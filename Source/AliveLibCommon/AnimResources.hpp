#pragma once
#include "FunctionFwd.hpp"

enum class AnimId
{
    None = 0,
    Abe_Head_Gib,
    Abe_Arm_Gib,
    Abe_Body_Gib,
    BlindMud_Head_Gib,
    BlindMud_Arm_Gib,
    BlindMud_Body_Gib,
    Glukkon_Head_Gib,
    Glukkon_Arm_Gib,
    Glukkon_Body_Gib,
    Aslik_Head_Gib,
    Aslik_Arm_Gib,
    Aslik_Body_Gib,
    Dripik_Head_Gib,
    Dripik_Arm_Gib,
    Dripik_Body_Gib,
    Phleg_Head_Gib,
    Phleg_Arm_Gib,
    Phleg_Body_Gib,
    Fleech_Head_Gib,
    Fleech_Body_Gib,
    Elum_Head_Gib,
    Elum_Arm_Gib,
    Elum_Body_Gib,
    Meat_Gib,
    Metal_Gib,
    Rock_Gib,
    Slig_Head_Gib,
    Slig_Arm_Gib,
    Slig_Body_Gib,
    Slog_Head_Gib,
    Slog_Body_Gib,
    Stick_Gib,

    Mudokon_RunToRoll,
    Mudokon_CrouchSpeak,
    Mudokon_ToCrouchSpeak,
    Mudokon_FallLandDie,
    Mudokon_PoisonGasDeath,
    Mudokon_ZShotRolling,
    Mudokon_ZShot,
    Mudokon_DoorEnter,
    Mudokon_DoorExit,
    Mudokon_WalkOffEdge,
    Mudokon_RunOffEdge,
    Mudokon_SneakOffEdge,
    Mudokon_HandstoneEnd,
    Mudokon_GrenadeMachineUse,
    Mudokon_HandstoneBegin,
    Mudokon_LedgeHang,
    Mudokon_LedgeDescend,
    Mudokon_RingRopePullHang,
    Mudokon_LedgeHangWobble,
    Mudokon_LedgeAscend,
    Mudokon_HopMid,
    Mudokon_HopLand,
    Mudokon_HopBegin,
    Mudokon_PickupItem,
    Mudokon_RollingKnockback,
    Mudokon_RollingKnockForward,
    Mudokon_LiftGrabIdle,
    Mudokon_LiftUseDown,
    Mudokon_AO_LiftUse,
    Mudokon_LiftGrabEnd,
    Mudokon_LiftGrabBegin,
    Mudokon_LiftUseUp,
    Mudokon_MineCarEnter,
    Mudokon_MineCarExit,
    Mudokon_PushWall,
    Mudokon_RockThrowStandingHold,
    Mudokon_RockThrowStandingEnd,
    Mudokon_RockThrowCrouchingHold,
    Mudokon_RockThrowCrouchingThrow,
    Mudokon_RockThrowStandingThrow,
    Mudokon_Rolling,
    Mudokon_RollingEnd_Unused,
    Mudokon_RollBegin,
    Mudokon_DunnoEnd,
    Mudokon_EndShrykull,
    Mudokon_ToShrykull,
    Mudokon_SlapBomb,
    Mudokon_Sorry,
    Mudokon_AfterSorry,
    Mudokon_ToSpeak,
    Mudokon_Null,
    Mudokon_RunJumpLand,
    Mudokon_RunTurnToWalk,
    Mudokon_RunJumpLandRun,
    Mudokon_RunJumpLandWalk,
    Mudokon_TurnToRun,
    Mudokon_HopToFall,
    Mudokon_RunJumpToFall,
    Mudokon_RollOffEdge,
    Mudokon_Well_Idle,
    Mudokon_WellBegin,
    Mudokon_JumpIntoWell,

    Bat,
    Bee_Swarm,

    Fleech_Climb,
    Fleech_SettleOnGround,
    Fleech_Consume,
    Fleech_Fall,
    Fleech_Sleeping,
    Fleech_Idle,
    Fleech_StopCrawling,
    Fleech_StopMidCrawlCycle,
    Fleech_Land,
    Fleech_SleepingWithTongue,
    Fleech_PatrolCry,
    Fleech_RaiseHead,
    Fleech_WakingUp,
    Fleech_Unused,
    Fleech_Knockback,
    Fleech_ExtendTongueFromEnemy,
    Fleech_RetractTongueFromEnemey,
    Fleech_DeathByFalling,
    Fleech_Crawl,

    Flying_Slig_Idle,
    Flying_Slig_Move_Horizontal,
    Flying_Slig_Idle_Turn_Around,
    Flying_Slig_Move_Down,
    Flying_Slig_Move_Down_Turn_Around,
    Flying_Slig_Move_Up,
    Flying_Slig_Move_Up_Turn_Around,
    Flying_Slig_Pull_Lever,
    Flying_Slig_Speak,
    Flying_Slig_Possession,
    Flying_Slig_Move_Horizontal_End,
    Flying_Slig_Move_Up_Start,
    Flying_Slig_Move_Horizontal_To_Down,
    Flying_Slig_Move_Up_To_Horizontal,
    Flying_Slig_Move_Down_To_Horizontal,
    Flying_Slig_Turn_Quick,
    Flying_Slig_Idle_To_Horizontal,
    FlyingSlig_BeginDownMovement,
    FlyingSlig_EndDownMovement,
    FlyingSlig_DownKnockback,
    FlyingSlig_UpKnockback,
    FlyingSlig_EndUpMovement,
    FlyingSlig_InstantUpXTurn,
    FlyingSlig_InstantDownXTurn,
    FlyingSlig_HorizontalToUpMovement,
    FlyingSlig_TurnToHorizontalMovement,

    Glukkon_Aslik_KnockBack,
    Glukkon_Aslik_Idle,
    Glukkon_Aslik_Jump,
    Glukkon_Aslik_Land,
    Glukkon_Aslik_LongLaugh,
    Glukkon_Aslik_ChantShake,
    Glukkon_Aslik_GetShot,
    Glukkon_Aslik_Speak1,
    Glukkon_Aslik_Speak2,
    Glukkon_Aslik_Speak3,
    Glukkon_Aslik_KnockBackStandBegin,
    Glukkon_Aslik_KnockBackStandEnd,
    Glukkon_Aslik_Turn,
    Glukkon_Aslik_JumpToFall,
    Glukkon_Aslik_WalkToFall,
    Glukkon_Aslik_Fall,
    Glukkon_Aslik_DeathFall,
    Glukkon_Aslik_BeginWalk,
    Glukkon_Aslik_EndWalk,
    Glukkon_Aslik_StandToJump,
    Glukkon_Aslik_JumpToStand,
    Glukkon_Aslik_WalkToJump,
    Glukkon_Aslik_JumpToWalk,
    Glukkon_Aslik_EndSingleStep,
    Glukkon_Aslik_Walk,

    Glukkon_Dripik_KnockBack,
    Glukkon_Dripik_Idle,
    Glukkon_Dripik_Jump,
    Glukkon_Dripik_Land,
    Glukkon_Dripik_LongLaugh,
    Glukkon_Dripik_ChantShake,
    Glukkon_Dripik_GetShot,
    Glukkon_Dripik_Speak1,
    Glukkon_Dripik_Speak2,
    Glukkon_Dripik_Speak3,
    Glukkon_Dripik_KnockBackStandBegin,
    Glukkon_Dripik_KnockBackStandEnd,
    Glukkon_Dripik_Turn,
    Glukkon_Dripik_JumpToFall,
    Glukkon_Dripik_WalkToFall,
    Glukkon_Dripik_Fall,
    Glukkon_Dripik_DeathFall,
    Glukkon_Dripik_BeginWalk,
    Glukkon_Dripik_EndWalk,
    Glukkon_Dripik_StandToJump,
    Glukkon_Dripik_JumpToStand,
    Glukkon_Dripik_WalkToJump,
    Glukkon_Dripik_JumpToWalk,
    Glukkon_Dripik_EndSingleStep,
    Glukkon_Dripik_Walk,

    Glukkon_Normal_KnockBack,
    Glukkon_Normal_Idle,
    Glukkon_Normal_Jump,
    Glukkon_Normal_Land,
    Glukkon_Normal_LongLaugh,
    Glukkon_Normal_ChantShake,
    Glukkon_Normal_GetShot,
    Glukkon_Normal_Speak1,
    Glukkon_Normal_Speak2,
    Glukkon_Normal_Speak3,
    Glukkon_Normal_KnockBackStandBegin,
    Glukkon_Normal_KnockBackStandEnd,
    Glukkon_Normal_Turn,
    Glukkon_Normal_JumpToFall,
    Glukkon_Normal_WalkToFall,
    Glukkon_Normal_Fall,
    Glukkon_Normal_DeathFall,
    Glukkon_Normal_BeginWalk,
    Glukkon_Normal_EndWalk,
    Glukkon_Normal_StandToJump,
    Glukkon_Normal_JumpToStand,
    Glukkon_Normal_WalkToJump,
    Glukkon_Normal_JumpToWalk,
    Glukkon_Normal_EndSingleStep,
    Glukkon_Normal_Walk,

    Glukkon_Phleg_KnockBack,
    Glukkon_Phleg_Idle,
    Glukkon_Phleg_Jump,
    Glukkon_Phleg_Land,
    Glukkon_Phleg_LongLaugh,
    Glukkon_Phleg_ChantShake,
    Glukkon_Phleg_GetShot,
    Glukkon_Phleg_Speak1,
    Glukkon_Phleg_Speak2,
    Glukkon_Phleg_Speak3,
    Glukkon_Phleg_KnockBackStandBegin,
    Glukkon_Phleg_KnockBackStandEnd,
    Glukkon_Phleg_Turn,
    Glukkon_Phleg_JumpToFall,
    Glukkon_Phleg_WalkToFall,
    Glukkon_Phleg_Fall,
    Glukkon_Phleg_DeathFall,
    Glukkon_Phleg_BeginWalk,
    Glukkon_Phleg_EndWalk,
    Glukkon_Phleg_StandToJump,
    Glukkon_Phleg_JumpToStand,
    Glukkon_Phleg_WalkToJump,
    Glukkon_Phleg_JumpToWalk,
    Glukkon_Phleg_EndSingleStep,
    Glukkon_Phleg_Walk,

    Greeter_Chase,
    Greeter_Falling,
    Greeter_Hit,
    Greeter_Moving,
    Greeter_Speak,
    Greeter_Turn,

    Mine_Car_Closed,
    Mine_Car_Open,
    Mine_Car_Shake_A,
    Mine_Car_Shake_B,
    Mine_Car_Tread_Idle,
    Mine_Car_Tread_Move_A,
    Mine_Car_Tread_Move_B,

    Mudokon_Chant,
    Mudokon_ChantEnd,
    Mudokon_Chisel,
    Mudokon_CrouchIdle,
    Mudokon_ToDuck,
    Mudokon_CrouchToStand,
    Mudokon_CrouchTurn,
    Mudokon_Duck,
    Mudokon_DuckToCrouch,
    Mudokon_Fall,
    Mudokon_KnockbackGetUp,
    Mudokon_SlapOwnHead,
    Mudokon_HoistIdle,
    Mudokon_LandSoft,
    Mudokon_HoistBegin,
    Mudokon_Idle,
    Mudokon_KnockForward,
    Mudokon_Knockback,
    Mudokon_LeverUse,
    Mudokon_Run,
    Mudokon_RunSlideStop,
    Mudokon_RunSlideTurn,
    Mudokon_Run_End_C,
    Mudokon_RunJumpMid,
    Mudokon_RunJumpBegin,
    Mudokon_CrouchScrub,
    Mudokon_DunnoBegin,
    Mudokon_Punch,
    Mudokon_Sling,
    Mudokon_StandScrubLoop,
    Mudokon_StandScrubLoopToPause,
    Mudokon_StandScrubPauseToLoop,
    Mudokon_StandScrubPause,
    Mudokon_IdleToStandScrub,
    Mudokon_StandScrubToIdle,
    Mudokon_Struggle,
    Mudokon_StruggleToCrouchChant,
    Mudokon_CrouchChant,
    Mudokon_CrouchChantToStruggle,
    Mudokon_DunnoMid,
    kNullAnimDetails,
    Mudokon_AO_M_15_Null,
    Mudokon_CrouchSpeak1,
    Mudokon_CrouchSpeak2,
    Mudokon_ElumWalkLoop,
    Mudokon_ElumIdle,
    Mudokon_ElumRunSlideStop,
    Mudokon_ElumRunTurn,
    Mudokon_AO_M_106_Null,
    Mudokon_ElumHopBegin,
    Mudokon_ElumHopMid,
    Mudokon_ElumHopLand,
    Mudokon_ElumRunJumpBegin,
    Mudokon_ElumRunJumpMid,
    Mudokon_ElumRunJumpLand,
    Mudokon_ElumTurn,
    Mudokon_ElumRunLoop,
    Mudokon_ElumSpeak,
    Mudokon_AO_M_116_Null,
    Mudokon_ElumWalkBegin,
    Mudokon_ElumRunBegin,
    Mudokon_AO_M_119_Null,
    Mudokon_ElumRunToWalk,
    Mudokon_ElumMidRunToWalk,
    Mudokon_ElumRunTurnToRun,
    Mudokon_ElumRunTurnToWalk,
    Mudokon_ElumWalkEnd,
    Mudokon_ElumMidWalkEnd,
    Mudokon_ElumBeesStruggling,
    Mudokon_ElumMountEnd,
    Mudokon_ElumUnmountBegin,
    Mudokon_ElumUnmountEnd,
    Mudokon_ElumMountBegin,
    Mudokon_ElumFallOffEdge,
    Mudokon_ElumFall,
    Mudokon_ElumLand,
    Mudokon_ElumJumpToFall,
    Mudokon_ElumKnockback,
    Mudokon_Idle_RubEyes,
    Mudokon_Idle_StretchArms,
    Mudokon_Idle_Yawn,
    Mudokon_AO_ToShrykull,
    Mudokon_AO_ShrykullEnd,
    Mudokon_AO_Unknown1,
    Mudokon_AO_Unknown2,
    Mudokon_AO_Unknown3,
    Mudokon_AO_Unknown4,
    Mudokon_Sneak,
    Mudokon_Sneak_End,
    Mudokon_WalkToSneak,
    Mudokon_StandToCrouch,
    Mudokon_Speak1,
    Mudokon_Speak3,
    Mudokon_Speak2,
    Mudokon_SpeakFart,
    Mudokon_StandingTurn,
    Mudokon_WalkBegin,
    Mudokon_WalkToIdle,
    Mudokon_MidWalkToIdle,
    Mudokon_AO_Null,
    Mudokon_StartChisel,
    Mudokon_StopChisel,
    Mudokon_WalkToRun,
    Mudokon_MidWalkToRun,
    Mudokon_RunToWalk,
    Mudokon_MidRunToWalk,
    Mudokon_RunTurnToRun,
    Mudokon_SneakToWalk,
    Mudokon_MidWalkToSneak,
    Mudokon_MidSneakToWalk,
    Mudokon_SneakBegin,
    Mudokon_SneakToIdle,
    Mudokon_MidSneakToIdle,
    Mudokon_StandToRun,
    Mudokon_FallingFromGrab,
    Mudokon_DuckKnockback,
    Mudokon_Walk,
    Mudokon_TurnWheel,
    Mudokon_TurnWheelEnd,
    Mudokon_TurnWheelBegin,

    Paramite_Attack,
    Paramite_WebGoingDown,
    Paramite_WebLeaveDown,
    Paramite_WebLeaveUp,
    Paramite_WebIdle,
    Paramite_WebGrab,
    Paramite_WebGoingUp,
    Paramite_Eating,
    Paramite_Death,
    Paramite_Idle,
    Paramite_WalkBegin,
    Paramite_JumpUpMidair,
    Paramite_JumpUpLand,
    Paramite_JumpUpBegin,
    Paramite_Walking,
    Paramite_RunningAttack,
    Paramite_Running,
    Paramite_Hop,
    Paramite_PreHiss,
    Paramite_Squawk,
    Paramite_AllOYaGameSpeakBegin,
    Paramite_GameSpeakEnd,
    Paramite_GameSpeakBegin,
    Paramite_Turn,
    Paramite_Unused,
    Paramite_WalkRunTransition,
    Paramite_WalkEnd,
    Paramite_RunBegin,
    Paramite_RunEnd,
    Paramite_Falling,
    Paramite_RopePull,
    Paramite_CloseAttack,
    Paramite_Landing,
    Paramite_Unused2,
    Paramite_Knockback,
    Paramite_SurpriseWeb,
    Paramite_Hiss,
    Paramite_PostHiss,

    Scrab_FeedToGulp,
    Scrab_Dance,
    Scrab_DeathEnd,
    Scrab_Feed,
    Scrab_StandToFeed,
    Scrab_Idle,
    Scrab_Jump,
    Scrab_LegKick,
    Scrab_HopBegin,
    Scrab_Landing,
    Scrab_Knockback,
    Scrab_Shriek,
    Scrab_Run,
    Scrab_RunToStand,
    Scrab_HowlBegin,
    Scrab_HowlEnd,
    Scrab_Turn,
    Scrab_JumpAndRunToFall,
    Scrab_StandToWalk,
    Scrab_StandToRun,
    Scrab_WalkToStand,
    Scrab_WalkToFall,
    Scrab_WalkToRun,
    Scrab_RunToWalk,
    Scrab_GetEaten,
    Scrab_Empty,
    Scrab_GulpToStand,
    Scrab_AttackLunge,
    Scrab_DeathBegin,
    Scrab_Walk,
    Scrab_AttackSpin,
    Scrab_ScrabBattleAnim,

    Crawling_Slig_Idle,
    Crawling_Slig_UsingButton,
    Crawling_Slig_WakingUp,
    Crawling_Slig_Crawling,
    Crawling_Slig_StartFalling,
    Crawling_Slig_Falling,
    Crawling_Slig_Landing,
    Crawling_Slig_ToShakingToIdle,
    Crawling_Slig_Speaking,
    Crawling_Slig_Snoozing,
    Crawling_Slig_PushingWall,
    Crawling_Slig_TurnAround,
    Crawling_Slig_Shaking,
    Crawling_Slig_Empty,
    Crawling_Slig_ShakingToIdle,
    Crawling_Slig_EndCrawling,
    Crawling_Slig_IdleToPushingWall,
    Crawling_Slig_EndPushingWall,

    Slig_Beat,
    Slig_OutToFall,
    Slig_LandingFatal,
    Slig_Smash,
    Slig_LandingSoft,
    Slig_FallingInitiate,
    Slig_KnockbackToStand,
    Slig_Idle,
    Slig_ShootToStand,
    Slig_Knockeback,
    Slig_PullLever,
    Slig_LiftGripping,
    Slig_LiftUp,
    Slig_LiftDown,
    Slig_LiftGrip,
    Slig_LiftUngrip,
    Slig_PossessShake,
    Slig_ReloadGun,
    Slig_Running,
    Slig_StandToRun,
    Slig_SlidingToStand,
    Slig_SlidingTurn,
    Slig_Shoot,
    Slig_Recoil,
    Slig_ShootZ,
    Slig_ShootZtoStand,
    Slig_SteppingToStand,
    Slig_Sleeping,
    Slig_Speak1,
    Slig_Speak2,
    Slig_Speak3,
    Slig_Speak4,
    Slig_TurnAroundStanding,
    Slig_Walking,
    Slig_StandToWalk,
    Slig_SlidingTurnToWalk,
    Slig_SlidingTurnToRun,
    Slig_StandingToStep,
    Slig_Gamespeak,
    Slig_WalkToStand,
    Slig_SleepingToStand,

    CrawlingSligButton,
    CrawlingSligButtonUse,
    BloodDrop,
    SpotLight,
    ShrykullStart,
    ShrykullTransform,
    ShrykullDetransform,
    NormalMudIcon,
    AngryMudIcon,
    HappyMudIcon,

    MenuHighlight_ButtonRemapSquare,
    MenuHighlight_Circle,
    MenuHighlight_Square,
    MenuHighlight_Triangle,

    MenuDoor,

    AbeIntro,

    MenuAbeSpeak_Laugh,
    MenuAbeSpeak_WhistleHigh,
    MenuAbeSpeak_WhistleLow,
    MenuAbeSpeak_Fart,
    MenuAbeSpeak_Hello,
    MenuAbeSpeak_Idle,
    MenuAbeSpeak_IdleBlink,
    MenuAbeSpeak_Ok,

    MenuAbeSpeak_FollowMe,
    MenuAbeSpeak_Wait,
    MenuAbeSpeak_Work,
    MenuAbeSpeak_Anger,
    MenuAbeSpeak_AllYa,
    MenuAbeSpeak_Sympathy,
    MenuAbeSpeak_StopIt,
    MenuAbeSpeak_Chant,
    MenuAbeSpeak_ChantEnd,
    MenuAbeSpeak_Goodbye,

    MenuGlukkonSpeak_Idle,
    MenuGlukkonSpeak_IdleVariation,
    MenuGlukkonSpeak_Hey,
    MenuGlukkonSpeak_Commere,
    MenuGlukkonSpeak_StayHere,
    MenuGlukkonSpeak_DoIt,
    MenuGlukkonSpeak_KillEm,
    MenuGlukkonSpeak_AllOYa,
    MenuGlukkonSpeak_Help,
    MenuGlukkonSpeak_Laugh,

    MenuScrabSpeak_Idle,
    MenuScrabSpeak_IdleVariation,
    MenuScrabSpeak_ShredPower,
    MenuScrabSpeak_Howl,

    MenuParamiteSpeak_Howdy,
    MenuParamiteSpeak_Idle,
    MenuParamiteSpeak_IdleVariation,
    MenuParamiteSpeak_Cmon,
    MenuParamiteSpeak_Stay,
    MenuParamiteSpeak_DoIt,
    MenuParamiteSpeak_Attack,
    MenuParamiteSpeak_AllAYa,

    MenuSligSpeak_Idle,
    MenuSligSpeak_Hi,
    MenuSligSpeak_HereBoy,
    MenuSligSpeak_Freeze,
    MenuSligSpeak_GetEm,
    MenuSligSpeak_SmoBs,
    MenuSligSpeak_Bs,
    MenuSligSpeak_LookOut,
    MenuSligSpeak_Laugh,

    Slog_MoveHeadUpwards,
    Slog_StartFastBarking,
    Slog_AngryBark,
    Slog_BROKEN_J,
    Slog_Dying,
    Slog_Eating,
    Slog_Fall,
    Slog_Idle,
    Slog_Growl,
    Slog_JumpUpwards,
    Slog_JumpForwards,
    Slog_Run,
    Slog_StopRunning,
    Slog_SlideTurn,
    Slog_Scratch,
    Slog_Sleeping,
    Slog_MoveHeadDownwards,
    Slog_Bark,
    Slog_TurnAround,
    Slog_StartWalking,
    Slog_EndWalking,
    Slog_Land,
    Slog_Unused,
    Slog_EndFastBarking,
    Slog_Walk,

    Slurg_Burst,
    Slurg_Move,
    Slurg_Turn_Around,

    BG_Brewery_Barrel_Anim,
    BG_Mine_Fan,
    BG_Feeco_Small_Fan,
    BG_Heat_Extractor_Fan,
    
    Background_Glukkon,
    Bell_Hammer,
    ObjectShadow,
    Elum_FallUnknown1,
    BirdPortal_TerminatorShrink,
    BirdPortal_Sparks,
    BirdPortal_Flash,
    PullRingRope_Idle,
    PullRingRope_UseEnd,
    PullRingRope_UseBegin,
    Blood,
    Bone,
    BoneBag_Idle,
    BoneBag_HardHit,
    BoneBag_SoftHit,
    Drill_Horizontal_Off,
    Drill_Horizontal_On,
    Drill_Vertical_Off,
    Drill_Vertical_On,
    Bullet_Shell,
    BigChime,
    MediumChime,
    SmallChime,
    Chime_Ball,
    Circular_Fade,
    DeathFlare_1,
    DeathFlare_2,
    HoistRock1,
    HoistRock2,
    HoistRock3,
    Dust_Particle,
    Loading_Icon,
    Loading_Icon2,
    Vaporize_Particle,
    ShootingFire_Particle,
    ChantOrb_Particle,
    SquibSmoke_Particle,
    Explosion_Rocks,
    Explosion_Sticks,
    Mine_Flash,
    OptionChantOrb_Particle,
    ShootingZFire_Particle,
    WaterSplash,
    BirdPortal_TerminatorGrow,
    BirdPortal_TerminatorIdle,
    WaterDrop,
    BrewMachine_Button,
    CrawlingSligLocker_Closed,
    CrawlingSligLocker_Open, 
    LiftPlatform_Mines,
    LiftBottomWheel_Mines,
    LiftTopWheel_Mines,
    LiftPlatform_Necrum,
    LiftBottomWheel_Necrum,
    LiftTopWheel_Necrum,
    Door_Barracks_Closed,
    Door_Barracks_Open,
    Door_BarracksMetal_Closed,
    Door_BarracksMetal_Open,
    Door_Bonewerkz_Closed,
    Door_Bonewerkz_Open,
    Door_Brewery_Closed,
    Door_Brewery_Open,
    Door_Feeco_Closed,
    Door_Feeco_Open,
    Fire,
    Door_FireBackgroundGlow,
    Door_Flame_Spark,
    Door_Lock_Idle,
    Door_Lock_Open,
    Door_Mines_Closed,
    Door_Mines_Open,
    Door_Temple_Closed,
    Door_Temple_Open,
    Door_Train_Closed,
    Door_Train_Closing,
    Dove_Idle,
    Dove_Flying,
    Electric_Wall,
    Explosion,
    Explosion_Mine,
    Explosion_Small,
    Falling_Crate_A,
    Falling_Crate_B,
    Falling_Rock_A,
    Falling_Rock_B,
    Fart,
    Foot_Switch_Bonewerkz_Idle,
    Foot_Switch_Bonewerkz_Pressed,
    Foot_Switch_Industrial_Idle,
    Foot_Switch_Industrial_Pressed,
    Foot_Switch_Temple,
    Foot_Switch_Vault_Idle,
    Foot_Switch_Vault_Pressed,
    Grenade,
    Grenade_Machine_Button_Off,
    BoomMachine_Button_On,
    BoomMachine_Nozzle,
    Grenade_Machine_Nozzle_Drop_Grenade,
    HintFly,
    Honey,
    Honey_Drip,
    Honey_Hive,
    Lift_Rope,
    Meat,
    MeatSack_Idle,
    MeatSack_Hit,
    MeatSaw,
    MeatSawMotor,
    Mine,
    MotionDetector_Flare,
    MotionDetector_Laser,
    MovingBomb,
    ParamiteWeb,
    Pullring_Desert,
    Pullring_Farms,
    Rock,
    RockSack_Idle,
    RockSack_SoftHit,
    RockSack_HardHit,
    Rope_R1,
    Rope_Lines,
    Security_Claw_Lower,
    Security_Claw_Upper,
    Security_Door,
    Security_Door_Idle,
    Security_Door_Speak,
    Security_Orb,
    Slam_Door_Industrial_Closed,
    Slam_Door_Industrial_Closing,
    Slam_Door_Industrial_Opening,
    Slam_Door_Vault_Closed,
    Slam_Door_Vault_Closing,
    Slam_Door_Vault_Opening,
    SlapLock_Initiate,
    SlapLock_Punched,
    SlapLock_Shaking,
    Sparks,
    Star,
    Status_Light_Green,
    Status_Light_Red,
    Stone_Ball,
    Stone_Ball_Stopper,
    Swinging_Ball_Fast,
    Swinging_Ball_Normal,
    Swinging_Ball_Slow,
    Switch_Idle,
    Switch_Pull_Left_A,
    Switch_Pull_Left_B,
    Switch_Pull_Right_A,
    Switch_Pull_Right_B,
    TimedMine_Activated,
    TimedMine_Idle,
    Tortured_Mudokon,
    Tortured_Mudokon_Released,
    Tortured_Mudokon_Zap,
    Trap_Door_Closed,
    Trap_Door_Closing,
    Trap_Door_Open,
    Trap_Door_Opening,
    Trap_Door_Tribal_Closed,
    Trap_Door_Tribal_Closing,
    Trap_Door_Tribal_Open,
    Trap_Door_Tribal_Opening,
    R1_TrapDoor_Open,
    R1_TrapDoor_Closed,
    R1_TrapDoor_Opening,
    R1_TrapDoor_Closing,
    Lines_TrapDoor_Open,
    Lines_TrapDoor_Closed,
    Lines_TrapDoor_Opening,
    Lines_TrapDoor_Closing,
    Desert_TrapDoor_Open,
    Desert_TrapDoor_Closed,
    Desert_TrapDoor_Opening,
    Desert_TrapDoor_Closing,
    UXB_Active,
    UXB_Disabled,
    UXB_Toggle,
    Bomb_Flash,
    Bomb_RedGreenTick,
    Well_Leaf,
    Work_Wheel_Idle,
    Work_Wheel_Turning,
    Zap_Line_Blue,
    Zap_Line_Red,
    Zap_Sparks,
    GoldGlow,
    GreenGlow,
    FlintGlow,
    GreenDoorLight,
    GreenHubLight,
    RedDoorLight,
    RedHubLight,
    FlintLock_Hammers_Activating,
    FlintLock_Hammers_Disabled,
    FlintLock_Gourd,
    LiftPlatform_Forest,
    LiftPlatform_RuptureFarms,
    LiftPlatform_Desert,
    LiftPlatform_Desert2,
    LiftPlatform_Lines,
    LiftBottomWheel_RuptureFarms,
    LiftBottomWheel_Lines,
    LiftBottomWheel_Forest,
    LiftBottomWheel_Desert,
    LiftBottomWheel_Desert2,
    LiftTopWheel_RuptureFarms,
    LiftTopWheel_Lines,
    LiftTopWheel_Forest,
    LiftTopWheel_Desert,
    LiftTopWheel_Desert2,

    Anim_Tester, // For animation testing with the TestAnimation.cpp, ignore this.
};

enum class PalId
{
    Default, // Don't override the anims default pal
    BlindMud,
};

struct PalDetails final
{
    const char_type* mBanName;
    s32 mResourceId;
};

struct CombinedPalRecord final
{
    PalId mId;
    PalDetails mAEData;
    PalDetails mAOData;
};

struct PalRecord final
{
    PalId mId;
    const char_type* mBanName;
    s32 mResourceId;
};

struct AnimDetails final
{
    const char_type* mBanName;
    s32 mFrameTableOffset;
    s16 mMaxW;
    s16 mMaxH;
    s32 mResourceId;
    PalId mPalOverride;
};

struct AnimRecord final
{
    AnimId mId;
    const char_type* mBanName;
    s32 mFrameTableOffset;
    s16 mMaxW;
    s16 mMaxH;
    s32 mResourceId;
    PalId mPalOverride;
};

struct CombinedAnimRecord final
{
    AnimId mId;
    AnimDetails mAEData;
    AnimDetails mAOData;
};

const PalRecord PalRec(PalId toFind);
const AnimRecord AnimRec(AnimId toFind);
void FrameTableOffsetExists(int frameTableOffset, bool isAe, int maxW, int maxH);
void FrameTableOffsetExists(int frameTableOffset, bool isAe);

namespace AO 
{
    const PalRecord PalRec(PalId toFind);
    const AnimRecord AnimRec(AnimId toFind);
}

// AE and AO resource ids
enum ResourceID
{
    kUnknownResID_0 = 0,
    kDemoResID = 1,
    kLcdfontResID = 2,
    kAbebasicResID = 10,
    kAbepullResID = 11,
    kAbepickResID = 12,
    kAbebombResID = 13,
    kAbethrowResID = 14,
    kAbewaspResID = 16,
    kAberingResID = 17,
    kAbesmashResID = 19,
    kAbefallResID = 20,
    kAbestoneResID = 21,
    kAbecrushResID = 22,
    kAbeblowResID = 25,
    kAbeknbkResID = 26,
    kAbeknfdResID = 27,
    kAbeknokzResID = 28,
    kAbeyawnResID = 31,
    kAberubResID = 32,
    kAbesizeResID = 33,
    kAbebordResID = 34,
    kAbeeyesResID = 35,
    kAbebuttResID = 36,
    kAbenutsResID = 37,
    kAbepnlkResID = 38,
    kAbewizzResID = 39,
    kAbetalkResID = 40,
    kAbehoistResID = 42,
    kAbeedgeResID = 43,
    kAbeswingResID = 44,
    kAbedoorResID = 45,
    kAbewellResID = 47,
    kAbeommResID = 48,
    kAbeliftResID = 53,
    kAbebsic1ResID = 55,
    kDovbasicResID = 60,
    kWaspResID = 61,
    kHintflyResID = 62,
    kBatBasicResID = 63,
    kFireFlyResID = 64,
    kDovshootResID = 66,
    kElumUnknownResID_100 = 100, // AO only
    kAneknbkResID = 106,         // AO only
    kAneedgeResID = 108,         // AO only
    kElumUnknownResID_110 = 110, // AO only
    kElumUnknownResID_112 = 112, // AO only
    kAbeCarResId = 113,
    kAneprmntResID = 115,
    kAbemorphResID = 117,
    kAbegasResID = 118,
    kShrmorphResID = 121,
    kUnknownResID_125 = 125,
    kAbespeakResID = 130,
    kAbeintroResID = 131,
    kAbespek2ResID = 132,
    kSligSpeakResID = 140,
    kGlukkonSpeakResID = 150,
    kParamiteSpeakResID = 160,
    kScrabSpeakResID = 170,
    kElmbasicResID_200 = 200, // AO only
    kHappyiconResID = 201,
    kAngryiconResID = 202,
    kNormaliconResID = 203,
    kUnknownResID_204 = 204,
    kElmnknbkResID = 215,    // AO only
    kElmfallResID_216 = 216, // AO only
    kElmblowResID_217 = 217,
    kElumUnknownResID_220 = 220, // AO only
    kElumUnknownResID_221 = 221, // AO only
    kElmprmntResID__222 = 222,   // AO only
    kElumUnknownResID_223 = 223, // AO only
    kElumUnknownResID_224 = 224, // AO only
    kElmaloneResID_230 = 230,    // AO only
    kBgexpldResID = 300,
    kExplo2ResID = 301,
    kAlrmFlarResID = 302,
    kDustResID = 303,
    kHubFireResID = 304,
    kVaporResID = 305,
    kSlurgResID = 306,
    kGreeterResID = 307,
    kOmmflareResID = 312,
    kPortalTerminatorID = 313,
    kSparksResID = 314,
    kSpotliteResID = 316,
    kSkiddustResID = 317,
    kSmokeResID = 318,
    kBigflashResID = 319,
    kWorkwhelResID = 320,
    kUnknownResID_333 = 333,
    kHoneyResID = 337,
    kWellLeafResID = 341,
    kSquibResID = 343,
    kZflashResID = 344,
    kFxflareResID = 348,
    kDeathFlareResID = 349,
    kAberockResID = 350,
    kPortliteResID = 351,
    kPortlitResID = 353,
    kSquibSmokeResID = 354,
    kSplineResID = 355,
    kHoistRocks = 357,
    kStickGib = 358,
    kShellResID = 360,
    kGlowResID = 361,
    kMetalGib = 365,
    kBloodropResID = 366,
    kOptionFlare = 367,
    kWaterDrop = 368,
    kSplashResID = 369,
    kSmallExplo2ResID = 372,
    kStatusLightResID = 373,
    kDoorLockResID_374 = 374,
    kTorturedMudTearsResID = 375,
    kSlgbasicResID = 412,
    kSlgsleepResID = 413,
    kSlgknbkResID = 414,
    kSlgedgeResID = 415,
    kSlgsmashResID = 416,
    kSlgzshotResID = 417,
    kSlgknfdResID = 418,
    kSlgleverResID = 419,
    kSlgliftResID = 420,
    kSligBlowResID = 423,
    kSlgbeatResID = 426,
    kCrawlingSligLockerResID_448 = 448,
    kCrawlingSligResID_449 = 449,
    kFlySligResID = 450,
    kSlingmudResID_508 = 508,
    kMudscrubResID = 510,
    kMudchslResID = 511,
    kMudidleResID = 512,
    kMudoduckResID = 514,
    kAbeworkResID = 515,
    kMudltusResID = 516,
    kMudbtlnkResID = 517,
    kTorturedMud = 518,
    kMudangryResID = 530,
    kMudsadResID = 531,
    kMudwiredResID = 532,
    kMudblindResID = 533,
    kMudsickResID = 534,
    kMudombieResID = 550,
    kDogbasicResID = 570,
    kDogrstnResID = 571,
    kDogattkResID = 572,
    kDogknfdResID = 573,
    kDogidleResID = 574,
    kSlogBlowResID = 576,
    kFleeBlowResID_580 = 580,
    kBoneBagResID_590 = 590,
    kBoneResID = 591,
    kArjbasicResID = 600,
    kArjeatResID = 601,
    kArjclimbResID = 604,
    kArjpumpResID = 605,
    kArjscrchResID = 609,
    kArjwaspResID = 610,
    kArjjumpResID = 611,
    kArjponceResID = 614,
    kArjfalrkResID = 615,
    kArsbasicResID = 700,
    kArseatResID = 701,
    kArsprceResID = 702,
    kArsskwrResID = 703,
    kArswhirlResID = 704,
    kArshowlResID = 705,
    kArsdanceResID = 706,
    kArssackResID = 707,
    kArsdeadResID = 708,
    kArsroarResID = 709,
    kArsgrwlResID = 710,
    kArschewResID = 711,
    kArscrshResID = 713,
    kGlkbasicResID = 800,
    kGlukkonResID_801 = 801,
    kGlukAslikResID = 802,
    kAslikResID_803 = 803,
    kGlukDripikResID = 804,
    kDripikResID_805 = 805,
    kGlukPhlegResID = 806,
    kPhlegResID_807 = 807,
    kGlukredResID = 825,
    kGlukgrenResID = 826,
    kGlukblueResID = 827,
    kGlukaquaResID = 828,
    kFleechResID = 900,
    kRopesResID = 1000,
    kLiftWheelsResID = 1001,
    kP2c2bagResID = 1002,
    kP5c1wlkResID = 1003,
    kP6c1trapResID = 1004,
    kBombResID = 1005,
    kGrenflshResID = 1006,
    kP4c5hiveResID = 1008,
    kSwitchResID = 1009,
    kBombflshResID = 1011,
    kP2c3HiveResID = 1013,
    kPullringResID = 1014,
    kP6c4tubeResID = 1017,
    kP7c1spikResID = 1018,
    kHammerResID = 1019,
    kCrystalResID = 1030,
    kLiftResID = 1032,
    kLandmineResID = 1036,
    kUXBResID = 1037,
    kBGStarResID = 1039,
    kMineflshResID = 1040,
    kP1c3tubeResID = 1050,
    kGhostTrpResID_1053 = 1053,
    kCrawlingSligButtonResID_1057 = 1057,
    kDebrisID00 = 1105,
    kTubeResID = 1200,

    kTestanimResID = 2000,

    kF2zballResID = 2001,
    kF2stnbalResID = 2002,
    kF2stnsckResID = 2003,
    kChimeResID = 2005,
    kMaimGameResID = 2006,
    kF2rockResID = 2007,
    kF2eyeorbResID = 2008,
    kPupilResID = 2009,
    kTriggerResID = 2010,
    kF2p3dorResID = 2012,
    kTrainDoorResID_2013 = 2013,
    kFlintLockResID = 2017,
    kRockdoorResID = 2018,
    kHubdoorResID = 2019,
    kSlamResID = 2020,
    kMeatResID = 2023,
    kF2ChimeBallResID = 2024,
    kF2ChimeRackResID = 2025,
    kGourdResID = 2028,
    kWebResID = 2034,
    kObjectShadowResID = 2035,
    kMovebombResID = 3006,
    kMeatSackResID = 4002,
    kElecwallResID = 6000,
    kMotionResID = 6001,
    kMflareResID = 6002,
    kMeatSawResID = 6003,
    kDrillResID = 6004,
    kGrenadeResID = 6005,
    kR1sdoorResID = 6006,
    kR1buttonResID = 6008,
    kR1bpipeResID = 6009,
    kGreenGlowResID_6010 = 6010, // AO only
    kGoldGlowResID_6011 = 6011,   // AO only
    kBayrollResID_6013 = 6013,
    kMeatGibResID_6014 = 6014, // AO only
    kBrewButtonResID_6016 = 6016,
    kEvilFartResID = 6017,
    kR1sdosResID_6027 = 6027,
    kFlintGlowResID_6028 = 6028,      // AO only
    kGreenDoorLightResID_6031 = 6031, // AO only
    kRedDoorLightResID_6032 = 6032,   // AO only
    kTwnkleResID = 7012,
    kControlsResID = 8000,
    kMenuDoorResID = 8001,
    kHighliteResID = 8002,
    kHighlitePalResID = 8003,
    kLoadingResID = 8010,
};

namespace AO {

enum AOResourceID
{
};

} // namespace AO
