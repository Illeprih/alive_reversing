#pragma once

#include "Sequencer.hpp"
#include <array>
#include "SDL.h"

namespace sean {

/////////////////////////////////
/// DuckStation

static const u32 NUM_SAMPLES_PER_ADPCM_BLOCK = 28;

u32 mask(u32 num)
{
    u32 res = 0;
    while (num-- > 0)
    {
        res = (res << 1) | 1;
    }
    return res;
}

template <typename TValue>
constexpr u16 Truncate16(TValue value)
{
    return static_cast<u16>(static_cast<typename std::make_unsigned<decltype(value)>::type>(value));
}

template <typename TReturn, typename TValue>
constexpr TReturn SignExtend(TValue value)
{
    return static_cast<TReturn>(
        static_cast<typename std::make_signed<TReturn>::type>(static_cast<typename std::make_signed<TValue>::type>(value)));
}

template <typename TValue>
constexpr u32 SignExtend32(TValue value)
{
    return SignExtend<u32, TValue>(value);
}

template <typename TReturn, typename TValue>
constexpr TReturn ZeroExtend(TValue value)
{
    return static_cast<TReturn>(static_cast<typename std::make_unsigned<TReturn>::type>(
        static_cast<typename std::make_unsigned<TValue>::type>(value)));
}

template <typename TValue>
constexpr u32 ZeroExtend32(TValue value)
{
    return ZeroExtend<u32, TValue>(value);
}

ADSR parseADSR(u16 adsr1, u16 adsr2)
{
    ADSR adsr;
    adsr.sustainLevel = (adsr1) &mask(4);
    adsr.decayRate = (adsr1 >> 4) & mask(4);
    adsr.attackRate = (adsr1 >> 8) & mask(7);
    adsr.attackExponential = (adsr1 >> 15) & mask(1);

    adsr.releaseRate = adsr2 & mask(5);
    adsr.releaseExponential = (adsr2 >> 5) & mask(1);
    adsr.sustainRate = (adsr2 >> 6) & mask(7);
    adsr.sustainDirection = (adsr2 >> 14) & mask(1);
    adsr.sustainExponential = (adsr2 >> 15) & mask(1);
    return adsr;
}

struct ADSRTableEntry
{
    s32 ticks;
    s32 step;
};
enum : u32
{
    NUM_ADSR_TABLE_ENTRIES = 128,
    NUM_ADSR_DIRECTIONS = 2 // increasing, decreasing
};
using ADSRTableEntries = std::array<std::array<ADSRTableEntry, NUM_ADSR_TABLE_ENTRIES>, NUM_ADSR_DIRECTIONS>;

static constexpr ADSRTableEntries ComputeADSRTableEntries()
{
    ADSRTableEntries entries = {};
    for (u32 decreasing = 0; decreasing < 2; decreasing++)
    {
        for (u32 rate = 0; rate < NUM_ADSR_TABLE_ENTRIES; rate++)
        {
            if (rate < 48)
            {
                entries[decreasing][rate].ticks = 1;
                if (decreasing != 0)
                    entries[decreasing][rate].step = static_cast<s32>(static_cast<u32>(-8 + static_cast<s32>(rate & 3)) << (11 - (rate >> 2)));
                else
                    entries[decreasing][rate].step = (7 - static_cast<s32>(rate & 3)) << (11 - (rate >> 2));
            }
            else
            {
                entries[decreasing][rate].ticks = 1 << (static_cast<s32>(rate >> 2) - 11);
                if (decreasing != 0)
                    entries[decreasing][rate].step = (-8 + static_cast<s32>(rate & 3));
                else
                    entries[decreasing][rate].step = (7 - static_cast<s32>(rate & 3));
            }
        }
    }

    return entries;
}

static constexpr ADSRTableEntries s_adsr_table = ComputeADSRTableEntries();

s32 Voice::interpolate()
{
    static constexpr std::array<s16, 0x200> gauss = {{
        -0x001, -0x001, -0x001, -0x001, -0x001, -0x001, -0x001, -0x001, //
        -0x001, -0x001, -0x001, -0x001, -0x001, -0x001, -0x001, -0x001, //
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, //
        0x0001, 0x0001, 0x0001, 0x0002, 0x0002, 0x0002, 0x0003, 0x0003, //
        0x0003, 0x0004, 0x0004, 0x0005, 0x0005, 0x0006, 0x0007, 0x0007, //
        0x0008, 0x0009, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, //
        0x000F, 0x0010, 0x0011, 0x0012, 0x0013, 0x0015, 0x0016, 0x0018, // entry
        0x0019, 0x001B, 0x001C, 0x001E, 0x0020, 0x0021, 0x0023, 0x0025, // 000..07F
        0x0027, 0x0029, 0x002C, 0x002E, 0x0030, 0x0033, 0x0035, 0x0038, //
        0x003A, 0x003D, 0x0040, 0x0043, 0x0046, 0x0049, 0x004D, 0x0050, //
        0x0054, 0x0057, 0x005B, 0x005F, 0x0063, 0x0067, 0x006B, 0x006F, //
        0x0074, 0x0078, 0x007D, 0x0082, 0x0087, 0x008C, 0x0091, 0x0096, //
        0x009C, 0x00A1, 0x00A7, 0x00AD, 0x00B3, 0x00BA, 0x00C0, 0x00C7, //
        0x00CD, 0x00D4, 0x00DB, 0x00E3, 0x00EA, 0x00F2, 0x00FA, 0x0101, //
        0x010A, 0x0112, 0x011B, 0x0123, 0x012C, 0x0135, 0x013F, 0x0148, //
        0x0152, 0x015C, 0x0166, 0x0171, 0x017B, 0x0186, 0x0191, 0x019C, //
        0x01A8, 0x01B4, 0x01C0, 0x01CC, 0x01D9, 0x01E5, 0x01F2, 0x0200, //
        0x020D, 0x021B, 0x0229, 0x0237, 0x0246, 0x0255, 0x0264, 0x0273, //
        0x0283, 0x0293, 0x02A3, 0x02B4, 0x02C4, 0x02D6, 0x02E7, 0x02F9, //
        0x030B, 0x031D, 0x0330, 0x0343, 0x0356, 0x036A, 0x037E, 0x0392, //
        0x03A7, 0x03BC, 0x03D1, 0x03E7, 0x03FC, 0x0413, 0x042A, 0x0441, //
        0x0458, 0x0470, 0x0488, 0x04A0, 0x04B9, 0x04D2, 0x04EC, 0x0506, //
        0x0520, 0x053B, 0x0556, 0x0572, 0x058E, 0x05AA, 0x05C7, 0x05E4, // entry
        0x0601, 0x061F, 0x063E, 0x065C, 0x067C, 0x069B, 0x06BB, 0x06DC, // 080..0FF
        0x06FD, 0x071E, 0x0740, 0x0762, 0x0784, 0x07A7, 0x07CB, 0x07EF, //
        0x0813, 0x0838, 0x085D, 0x0883, 0x08A9, 0x08D0, 0x08F7, 0x091E, //
        0x0946, 0x096F, 0x0998, 0x09C1, 0x09EB, 0x0A16, 0x0A40, 0x0A6C, //
        0x0A98, 0x0AC4, 0x0AF1, 0x0B1E, 0x0B4C, 0x0B7A, 0x0BA9, 0x0BD8, //
        0x0C07, 0x0C38, 0x0C68, 0x0C99, 0x0CCB, 0x0CFD, 0x0D30, 0x0D63, //
        0x0D97, 0x0DCB, 0x0E00, 0x0E35, 0x0E6B, 0x0EA1, 0x0ED7, 0x0F0F, //
        0x0F46, 0x0F7F, 0x0FB7, 0x0FF1, 0x102A, 0x1065, 0x109F, 0x10DB, //
        0x1116, 0x1153, 0x118F, 0x11CD, 0x120B, 0x1249, 0x1288, 0x12C7, //
        0x1307, 0x1347, 0x1388, 0x13C9, 0x140B, 0x144D, 0x1490, 0x14D4, //
        0x1517, 0x155C, 0x15A0, 0x15E6, 0x162C, 0x1672, 0x16B9, 0x1700, //
        0x1747, 0x1790, 0x17D8, 0x1821, 0x186B, 0x18B5, 0x1900, 0x194B, //
        0x1996, 0x19E2, 0x1A2E, 0x1A7B, 0x1AC8, 0x1B16, 0x1B64, 0x1BB3, //
        0x1C02, 0x1C51, 0x1CA1, 0x1CF1, 0x1D42, 0x1D93, 0x1DE5, 0x1E37, //
        0x1E89, 0x1EDC, 0x1F2F, 0x1F82, 0x1FD6, 0x202A, 0x207F, 0x20D4, //
        0x2129, 0x217F, 0x21D5, 0x222C, 0x2282, 0x22DA, 0x2331, 0x2389, // entry
        0x23E1, 0x2439, 0x2492, 0x24EB, 0x2545, 0x259E, 0x25F8, 0x2653, // 100..17F
        0x26AD, 0x2708, 0x2763, 0x27BE, 0x281A, 0x2876, 0x28D2, 0x292E, //
        0x298B, 0x29E7, 0x2A44, 0x2AA1, 0x2AFF, 0x2B5C, 0x2BBA, 0x2C18, //
        0x2C76, 0x2CD4, 0x2D33, 0x2D91, 0x2DF0, 0x2E4F, 0x2EAE, 0x2F0D, //
        0x2F6C, 0x2FCC, 0x302B, 0x308B, 0x30EA, 0x314A, 0x31AA, 0x3209, //
        0x3269, 0x32C9, 0x3329, 0x3389, 0x33E9, 0x3449, 0x34A9, 0x3509, //
        0x3569, 0x35C9, 0x3629, 0x3689, 0x36E8, 0x3748, 0x37A8, 0x3807, //
        0x3867, 0x38C6, 0x3926, 0x3985, 0x39E4, 0x3A43, 0x3AA2, 0x3B00, //
        0x3B5F, 0x3BBD, 0x3C1B, 0x3C79, 0x3CD7, 0x3D35, 0x3D92, 0x3DEF, //
        0x3E4C, 0x3EA9, 0x3F05, 0x3F62, 0x3FBD, 0x4019, 0x4074, 0x40D0, //
        0x412A, 0x4185, 0x41DF, 0x4239, 0x4292, 0x42EB, 0x4344, 0x439C, //
        0x43F4, 0x444C, 0x44A3, 0x44FA, 0x4550, 0x45A6, 0x45FC, 0x4651, //
        0x46A6, 0x46FA, 0x474E, 0x47A1, 0x47F4, 0x4846, 0x4898, 0x48E9, //
        0x493A, 0x498A, 0x49D9, 0x4A29, 0x4A77, 0x4AC5, 0x4B13, 0x4B5F, //
        0x4BAC, 0x4BF7, 0x4C42, 0x4C8D, 0x4CD7, 0x4D20, 0x4D68, 0x4DB0, //
        0x4DF7, 0x4E3E, 0x4E84, 0x4EC9, 0x4F0E, 0x4F52, 0x4F95, 0x4FD7, // entry
        0x5019, 0x505A, 0x509A, 0x50DA, 0x5118, 0x5156, 0x5194, 0x51D0, // 180..1FF
        0x520C, 0x5247, 0x5281, 0x52BA, 0x52F3, 0x532A, 0x5361, 0x5397, //
        0x53CC, 0x5401, 0x5434, 0x5467, 0x5499, 0x54CA, 0x54FA, 0x5529, //
        0x5558, 0x5585, 0x55B2, 0x55DE, 0x5609, 0x5632, 0x565B, 0x5684, //
        0x56AB, 0x56D1, 0x56F6, 0x571B, 0x573E, 0x5761, 0x5782, 0x57A3, //
        0x57C3, 0x57E2, 0x57FF, 0x581C, 0x5838, 0x5853, 0x586D, 0x5886, //
        0x589E, 0x58B5, 0x58CB, 0x58E0, 0x58F4, 0x5907, 0x5919, 0x592A, //
        0x593A, 0x5949, 0x5958, 0x5965, 0x5971, 0x597C, 0x5986, 0x598F, //
        0x5997, 0x599E, 0x59A4, 0x59A9, 0x59AD, 0x59B0, 0x59B2, 0x59B3  //
    }};

    // the interpolation index is based on the source files sample rate
    const u8 i = (u8)vounter.interpolation_index();
    const u32 s = ZeroExtend32(vounter.sample_index());

    // interpolate on 4 most recent samples
    s32 out = 0;
    out += s32(gauss[0x0FF - i]) * s32(sample->buffer[(int) (f_SampleOffset + s) - 3]); // oldest s16 - but should it be s8?
    out += s32(gauss[0x1FF - i]) * s32(sample->buffer[(int) (f_SampleOffset + s) - 2]); // older
    out += s32(gauss[0x100 + i]) * s32(sample->buffer[(int) (f_SampleOffset + s) - 1]); // old
    out += s32(gauss[0x000 + i]) * s32(sample->buffer[(int) (f_SampleOffset + s) - 0]); // new

    return out >> 15;
}

/// DuckStation END
/////////////////////////////////

Sequencer::Sequencer()
{
    gseq = this;

    // Open SDL
    SDL_Init(SDL_INIT_AUDIO);

    SDL_AudioSpec waveSpec;
    waveSpec.callback = SDLCallback;
    waveSpec.userdata = nullptr;
    waveSpec.channels = 2;
    waveSpec.freq = 44100;
    waveSpec.samples = 512;
    waveSpec.format = AUDIO_F32;

    /* Open the audio device */
    if (SDL_OpenAudio(&waveSpec, NULL) < 0)
    {
        fprintf(stderr, "Failed to initialize audio: %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_PauseAudio(0);

    int id = 1;
    for (int i = 0; i < voiceCount; i++)
    {
        voices[i] = new Voice();
        voices[i]->id = id;
        id = id << 1;
    }

    for (int i = 0; i < patchCount; i++)
    {
        patches[i] = NULL;
    }

    //running = true;
    //thread = new std::thread(&Sequencer::loop, this);
}

Sequencer::~Sequencer()
{
    //running = false;
    //thread->join();
    //delete thread;

    // Delete buffers (by killing the instrument)
    for (Patch* patch : patches)
    {
        delete patch;
    }
}

u64 timeSinceEpochMillisec()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void Sequencer::loop()
{
    u64 start = timeSinceEpochMillisec();
    u64 now = 0;
    u64 currentTicks = 0;
    u64 expectedTicks = 0;
    while (running)
    {
        now = timeSinceEpochMillisec();
        expectedTicks = u64(float(now - start) / 1000.0f * 44100);

        // tick sequence - i.e. new notes to play/stop?
        tickSequence();

        while (currentTicks++ < expectedTicks)
        {
            // tick voices - just math calculations.
            // this is ticked 44100 times per second. Possibly this
            // can be done with a fast math calculation instead of
            // a loop, but that's for another time...
            tickVoice();
        }

        // sync voices with openal
        syncVoice();

        // defer this thread some amount of time
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void SDLCallback(void* udata, Uint8* stream, int len)
{
    udata;
    stream;
    len;

    // This runs at 44100hz
    // 1. tick voices
    //      a. interpolate
    //      b. adsr
    //      c. pitch (this seems like it should be before interpolation though...)
    // 2. run reverb

    gseq->tickSequence();

    float* AudioStream = (float*) stream;
    int StreamLength = len / sizeof(float);
    float leftSample = 0;
    float rightSample = 0;
    for (int i = 0; i < StreamLength; i += 2)
    {
        // set silence if no voice is played
        AudioStream[i] = 0;
        AudioStream[i + 1] = 0;

        // mix voices
        for (Voice* v : gseq->voices)
        {
            if (!v->sample || v->complete)
            {
                continue;
            }

            std::tuple<s32, s32> s = v->tick();
            // Tick voice
            leftSample = (float) std::get<0>(s) / 32767.0f; // * v->leftPan;
            rightSample = (float) std::get<1>(s) / 32767.0f; // * v->rightPan;

            // 32767.0f is max of signed 16 bit integer
            //float add = v->sample->SampleRate / 44100.0f;
            //leftSample = (float) (v->sample->buffer[(int) v->f_SampleOffset]) / 32767.0f;
            //v->f_SampleOffset = v->f_SampleOffset + add;
            ////rightSample = (float) (v->sample->buffer[(int) v->f_SampleOffset++]) / 32767.0f;
            //rightSample = leftSample;

            // Run reverb
            // TODO

            // Set against SDL
            SDL_MixAudioFormat((Uint8*) (AudioStream + i), (const Uint8*) &leftSample, AUDIO_F32, sizeof(float), 37);      // Left Channel
            SDL_MixAudioFormat((Uint8*) (AudioStream + i + 1), (const Uint8*) &rightSample, AUDIO_F32, sizeof(float), 37); // Right Channel
        }
    }
}

//////////////////////////
// PRIVATE
void Sequencer::reset()
{
    stopAll();
    
    //for (s16 i = 0; i < patchCount; i++)
    //{
    //    // must be deleted separately from sources
    //    // since deleting a patch may delete a buffer
    //    // attached to a source
    //    delete patches[i];
    //    patches[i] = NULL;
    //}
    //
    //for (Sequence* seq : sequences)
    //{
    //    delete seq;
    //}
    //sequences.clear();
}

void Sequencer::stopAll()
{
    for (Sequence* seq : sequences)
    {
        seq->play = false;
    }

    for (s16 i = 0; i < voiceCount; i++)
    {
        releaseVoice(voices[i]);
    }
}

void Sequencer::playSeq(s32 seqId)
{
    for (Sequence* seq : sequences)
    {
        if (seq->id == seqId)
        {
            seq->repeats = 0;
            seq->play = true;
        }
    }
}


void Sequencer::stopSeq(s32 seqId)
{
    for (Sequence* seq : sequences)
    {
        if (seq->id == seqId)
        {
            seq->play = false;
            for (Voice* v : voices)
            {
                if (v && v->sequence == seq)
                {
                    v->offTime = timeSinceEpochMillisec();
                }
            }
        }
    }
}

void Sequencer::tickSequence()
{
    u64 now = timeSinceEpochMillisec();

    // Tick sequences
    for (Sequence* seq : sequences)
    {
        if (!seq || !seq->play)
        {
            continue;
        }

        if (seq->repeats > seq->repeatLimit)
        {
            stopSeq(seq->id);
            continue;
        }

        MIDIMessage* message;
        while ((message = seq->next(now)) != NULL)
        {
            switch (message->type)
            {
                case NOTE_ON:
                {
                    if (!seq->channels[message->channelId]->patch)
                    {
                        break;
                    }

                    for (Sample* sample : seq->channels[message->channelId]->patch->samples)
                    {
                        if (!sample)
                        {
                            continue;
                        }

                        if (message->note > sample->maxNote || message->note < sample->minNote)
                        {
                            continue;
                        }

                        Voice* v = obtainVoice();
                        if (!v)
                        {
                            continue;
                        }

                        v->sequence = seq;
                        v->patchId = seq->channels[message->channelId]->patch->id;
                        v->channelId = message->channelId;
                        v->pitchMin = 0;
                        v->velocity = message->velocity / 127.0f;
                        v->note = message->note;
                        v->sample = sample;
                        v->pan = 0;
                        v->loop = sample->adsr.attackRate > 0;  // attack is greater than sample length? sample->adsr.attackRate / 1000 > 1;
                    }

                    break;
                }
                case NOTE_OFF:
                {
                    for (Voice* v : voices)
                    {
                        if (v && v->sequence == seq && v->note == message->note)
                        {
                            v->offTime = now;
                        }
                    }
                    break;
                }
                case PATCH_CHANGE:
                {
                    seq->channels[message->channelId]->patch = patches[message->patchId];
                    break;
                }
                case END_TRACK:
                {
                    // repeats are handled in the sequence when messages starts at position 0 again
                    break;
                }
                case PITCH_BEND:
                {
                    for (int i = 0; i < voiceCount; i++)
                    {
                        if (voices[i]->inUse && voices[i]->channelId == message->channelId)
                        {
                            voices[i]->pitch = message->bend;
                        }
                    }
                    break;
                }
            }
        }
    }
}

void Sequencer::tickVoice()
{
    for (int c = 0; c < voiceCount; c++)
    {
        Voice* voice = voices[c];
        if (!voice->inUse)
        {
            continue;
        }

         voice->tick();
    }
}

void Sequencer::syncVoice()
{
    for (int c = 0; c < voiceCount; c++)
    {
        Voice* voice = voices[c];
        if (!voice->inUse)
        {
            continue;
        }

        if (!voice->sample)
        {
            continue;
        }

        // Update the play source paramters
        Sample* sample = voice->sample;

        // If we are past the duration of the notes playback
        //alGetSourcei(id, AL_SOURCE_STATE, &state);
        //if (state != AL_PLAYING)
        //{
        //    releaseVoice(voice);
        //    continue;
        //}

        //u8 note = voice->note;
        //s32 notePitch = voice->pitch < voice->pitchMin ? voice->pitchMin : voice->pitch; // or sample?
        //u8 rootNote = sample->rootNote;
        //u8 rootPitch = sample->rootNotePitchShift;
        // This figures out the frequency of midi notes (ex. 60 is middle C and 261.63 hz)
        // noteFreq is the note we want to play
        // rootFreq is the samples root note
        // We then divide the two to figure out how to pitch shift the sample to match the
        // the desired note. For some reason we have to multiply it by 2. don't know why.
        //float noteFreq = float(pow(2.0, float(note + (notePitch / 127.0f)) / 12.0f));
        //float rootFreq = float(pow(2.0, float(rootNote + (rootPitch / 127.0f)) / 12.0f));
        //float freq = noteFreq / rootFreq * 2.0f;
        float pan = voice->pan;

        if (sample->pan)
        {
            pan = sample->pan;
        }

        float seqVolume = 1.0f;
        if (voice->sequence)
        {
            seqVolume = voice->sequence->volume;
        }
        float gain = float(voice->adsrCurrentLevel) / 32767.0f * voice->velocity * voice->sample->volume* seqVolume;

        //alSource3f(id, AL_POSITION, pan, 0, -sqrtf(1.0f - pan * pan));
        //alSourcef(id, AL_PITCH, (ALfloat) freq);
        //alSourcef(id, AL_GAIN, (ALfloat) gain);
        //alSourcei(id, AL_LOOPING, voice->loop);

        // 0 Off
        // 1 Vibrate
        // 2 Portamento
        // 3 1 & 2(Portamento and Vibrate on)
        // 4 Reverb
        

        if (gain < 0.001f && voice->offTime > 0)
        {
            releaseVoice(voice);
        }
    }
}

static constexpr s32 ApplyVolume(s32 sample, s16 volume)
{
    return (sample * s32(volume)) >> 15;
}

std::tuple<s32, s32> Voice::tick()
{
    if (!sample)
    {
        return std::make_tuple(0, 0);
    }

    // INTERPOLATION
    s32 notePitch = pitch < pitchMin ? pitchMin : pitch; // or sample?
    u8 rootNote = sample->rootNote;
    u8 rootPitch = sample->rootNotePitchShift;

    // frequencies are stable for duration of note? - move elsewhere to cut down on maths?
    float noteFreq = float(pow(2.0, float(note + (notePitch / 127.0f)) / 12.0f));
    float rootFreq = float(pow(2.0, float(rootNote + (rootPitch / 127.0f)) / 12.0f));
    //float freq = (float) ((noteFreq / rootFreq) * (float(sample->SampleRate) / 44100.0f));
    //f_SampleOffset += freq;


    if (vounter.sample_index() >= NUM_SAMPLES_PER_ADPCM_BLOCK)
    {
        // shift << 12 as sample_index is shifted over 12
        vounter.bits -= (NUM_SAMPLES_PER_ADPCM_BLOCK << 12);
        f_SampleOffset += NUM_SAMPLES_PER_ADPCM_BLOCK;
    }


    if (f_SampleOffset + vounter.sample_index() >= sample->len - 1 && !loop)
    {
        complete = true;
        return std::make_tuple(0, 0);
    }

    f_SampleOffset = f_SampleOffset + vounter.sample_index() >= sample->len ? 3 : f_SampleOffset;

    s32 sampleData;
    sampleData = interpolate();

    // duckstation uses this to get the actual sample rate in hz
    // (float(v.regs.adpcm_sample_rate) / 4096.0f) * 44100.0f)

    u16 step = (u16) (((float(sample->SampleRate) * (noteFreq / rootFreq)) / 44100.0f) * 4096.0f);
    //const s32 factor = std::clamp<s32>(sampleData, -0x8000, 0x7FFF) + 0x8000;
    //step = Truncate16(static_cast<u32>((SignExtend32(step) * factor) >> 15));
    step = std::min<u16>(step, 0x3FFF);
    vounter.bits += step;

    //s32 volume;
    //volume = ApplyVolume(sampleData, 1); //  voice.regs.adsr_volume

    // UPDATE ADSR STATE - this probably doesn't need to be done every tick?
    if (adsrPhase == NONE)
    {
        std::cout << sample->adsr.attackRate << " " << velocity << std::endl;
        adsrPhase = ATTACK;
        adsrDecreasing = false;
        adsrRate = sample->adsr.attackRate;
        adsrExponential = sample->adsr.attackExponential;
        adsrTargetLevel = MAX_VOLUME;
        adsrCounter = s_adsr_table[adsrDecreasing][adsrRate].ticks;
        //adsrCurrentLevel = MAX_VOLUME;
    }
    else if (adsrPhase == ATTACK && adsrCurrentLevel >= adsrTargetLevel)
    {
        adsrPhase = DECAY;
        adsrDecreasing = true;
        adsrRate = sample->adsr.decayRate << 2;
        adsrExponential = true;
        adsrTargetLevel = static_cast<s16>(std::min<s32>((u32(sample->adsr.sustainLevel) + 1) * 0x800, MAX_VOLUME));
        adsrCounter = s_adsr_table[adsrDecreasing][adsrRate].ticks;
    }
    else if (adsrPhase == DECAY && adsrCurrentLevel <= adsrTargetLevel)
    {
        adsrPhase = SUSTAIN;
        adsrDecreasing = sample->adsr.sustainDirection;
        adsrRate = sample->adsr.sustainRate;
        adsrExponential = sample->adsr.sustainExponential;
        adsrTargetLevel = 0;
        adsrCounter = s_adsr_table[adsrDecreasing][adsrRate].ticks;
    }
    else if (offTime != 0 && adsrPhase != RELEASE)
    {
        adsrPhase = RELEASE;
        adsrDecreasing = true;
        adsrRate = sample->adsr.releaseRate << 2;
        adsrExponential = sample->adsr.releaseExponential;
        adsrTargetLevel = 0;
        adsrCounter = s_adsr_table[adsrDecreasing][adsrRate].ticks;
        //adsrCurrentLevel = MIN_VOLUME;
    }


    // UPDATE TICK STATE
    adsrCounter--;
    if (adsrCounter <= 0)
    {
        const ADSRTableEntry& table_entry = s_adsr_table[adsrDecreasing][adsrRate];
        s32 this_step = table_entry.step;
        adsrCounter = table_entry.ticks;

        if (adsrExponential)
        {
            if (adsrDecreasing)
            {
                this_step = (this_step * adsrCurrentLevel) >> 15;
            }
            else
            {
                if (adsrCurrentLevel >= 0x6000)
                {
                    if (adsrRate < 40)
                    {
                        this_step >>= 2;
                    }
                    else if (adsrRate >= 44)
                    {
                        adsrCounter >>= 2;
                    }
                    else
                    {
                        this_step >>= 1;
                        adsrCounter >>= 1;
                    }
                }
            }
        }

        adsrCurrentLevel = static_cast<s16>(
            std::clamp<s32>(static_cast<s32>(adsrCurrentLevel) + this_step, MIN_VOLUME, MAX_VOLUME));
    }

    float centerPan = pan == 0 ? sample->pan : pan;
    float leftPan = 1.0f;
    float rightPan = 1.0f;
    if (centerPan > 0)
    {
        leftPan = 1.0f - abs(centerPan);
    }
    if (centerPan < 0)
    {
        rightPan = 1.0f - abs(centerPan);
    }

    float add = 1;
    if (sequence)
    {
        add = sequence->volume;
    }
    const float tmp = float(sampleData) * float(adsrCurrentLevel) / float(MAX_VOLUME) * velocity * add;
    const s32 left = s32(tmp * leftPan); // ApplyVolume(volume, voice.left_volume.current_level);
    const s32 right = s32(tmp * rightPan); //ApplyVolume(volume, voice.right_volume.current_level);
    //voice.left_volume.Tick();
    //voice.right_volume.Tick();
    return std::make_tuple(left, right);
}

Voice* Sequencer::obtainVoice()
{
    bool expected = false;
    for (int i = 0; i < voiceCount; i++)
    {
        Voice* v = voices[i];
        if (v->complete)
        {
            releaseVoice(v);
        }

        if (v->inUse.compare_exchange_weak(expected, true))
        {
            return v;
        }
    }
    return NULL;
}

void Sequencer::releaseVoice(Voice* v)
{
    v->offTime = 0;
    v->pitch = 0;
    v->adsrPhase = NONE;
    v->adsrCounter = 0;
    v->adsrCurrentLevel = 0;
    v->adsrTargetLevel = MAX_VOLUME;
    v->sequence = NULL;
    v->loop = false;
    v->pan = 0;
    v->f_SampleOffset = 0;
    v->vounter.bits = 0;
    v->complete = false;
    v->inUse = false;
}

//////////////////////////
// PUBLIC
Patch* Sequencer::createPatch(s16 id)
{
    if (patches[id])
    {
        return patches[id];
    }

    patches[id] = new Patch();
    patches[id]->id = (u8)id;
    return patches[id];
}

Sequence* Sequencer::createSequence()
{
    Sequence* seq = new Sequence();
    sequences.push_back(seq);
    return seq;
}

Sequence* Sequencer::getSequence(s32 id)
{
    for (Sequence* seq : sequences)
    {
        if (seq->id == id)
        {
            return seq;
        }
    }
    return NULL;
}

s32 Sequencer::playNote(s32 patchId, u8 note, float velocity, float pan, u8 pitch, s32 pitchMin, s32 pitchMax)
{    
    Patch* patch = patches[patchId];
    if (!patch)
    {
        return 0;
    }

    int ids = 0;
    for (Sample* s : patch->samples)
    {
        if (!s)
        {
            continue;
        }

        if (note > s->maxNote || note < s->minNote)
        {
            continue;
        }

        Voice* v = obtainVoice();
        if (!v)
        {
            return 0;
        }

        v->patchId = (u8) patchId;
        v->note = note;
        v->velocity = velocity;
        v->pan = pan;
        v->pitch = pitch;
        v->pitchMin = pitchMin;
        v->pitchMax = pitchMax;
        v->sample = s;
        ids |= v->id;
    }

    return ids;
}

void Sequencer::stopNote(s32 mask)
{
    for (int i = 0; i < voiceCount; i++)
    {
        if ((voices[i]->id & mask) != 0)
        {
            // TODO - not sure if this is right.
            // Maybe it should trigger a release?
            releaseVoice(voices[i]);
        }
    }
}

//////////////////////////
// SEQUENCE
MIDIMessage* Sequence::createMIDIMessage()
{
    MIDIMessage* msg = new MIDIMessage();
    messages.push_back(msg);
    return msg;
}

MIDIMessage* Sequence::next(u64 now)
{
    if (messages.size() <= 0)
    {
        return NULL;
    }

    if (actionPos == 0)
    {
        // the track is just starting if we are at pos 0
        trackStartTime = now;
    }

    u64 runtimeUs = std::max((u64) 0, now - trackStartTime) * 1000; // x1000 to conver to microseconds
    float midiTickUs = tempoUs / ticksPerBeat;
    u64 trackTick = u64(runtimeUs / midiTickUs);

    MIDIMessage* msg = messages.at(actionPos);
    if (msg->tick <= trackTick)
    {
        actionPos++;
        if (actionPos == messages.size())
        {
            actionPos = 0;
            repeats++; // we've looped the sequence
        }
        return msg;
    }
    return NULL;
}


//////////////////////////
// Event Ring
void EventRing::push(Event event)
{
    events[(head++) % size] = event;
}

Event* EventRing::pop()
{
    if (tail == head)
    {
        return NULL;
    }
    return &events[(tail++)];
}

} // namespace