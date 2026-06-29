#include "WK_GameplayTags.h"

namespace WKGameplayTags
{
	/* Player - Status */
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_Movement_Run,    "Player.Status.Movement.Run");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_Movement_Sprint,"Player.Status.Movement.Sprint");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_Movement_Walk,  "Player.Status.Movement.Walk");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_Movement_Idle,  "Player.Status.Movement.Idle");

	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_WaitForInput,   "Player.Status.WaitForInput");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_Turn,           "Player.Status.Turn");

	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_Attack_Light,   "Player.Status.Attack.Light");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_Attack_Charge,  "Player.Status.Attack.Charge");

	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_Dodge,          "Player.Status.Dodge");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_PerfectDodge,  "Player.Status.PerfectDodge");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_Invincible,    "Player.Status.Invincible");

	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_Jump,           "Player.Status.Jump");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_TargetLock,    "Player.Status.TargetLock");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_BlockInput,    "Player.Status.BlockInput");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_Charging,      "Player.Status.Charging");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_NoStamina,     "Player.Status.NoStamina");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_HitReact,      "Player.Status.HitReact");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_Parry,         "Player.Status.Parry");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Status_Hide,          "Player.Status.Hide");



	/* Player - Input */
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Move, "Player.Input.Move");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Look, "Player.Input.Look");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Jump, "Player.Input.Jump");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Turn, "Player.Input.Turn");

	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Movement_Run,    "Player.Input.Movement.Run");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Movement_Sprint,"Player.Input.Movement.Sprint");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Movement_Walk,  "Player.Input.Movement.Walk");

	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Held,    "Player.Input.Held");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Toggle,  "Player.Input.Toggle");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Trigger, "Player.Input.Trigger");

	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Held_ChargeAttack, "Player.Input.Held.ChargeAttack");

	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Trigger_Attack_Light,  "Player.Input.Trigger.Attack.Light");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Trigger_Dodge,         "Player.Input.Trigger.Dodge");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Trigger_Freeze,        "Player.Input.Trigger.Freeze");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Trigger_StopAndParry,  "Player.Input.Trigger.StopAndParry");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Trigger_RecoverHealth, "Player.Input.Trigger.RecoverHealth");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Trigger_Hide,          "Player.Input.Trigger.Hide");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Trigger_SummonMonkey,  "Player.Input.Trigger.SummonMonkey");

	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Input_Toggle_TargetLock, "Player.Input.Toggle.TargetLock");


	/* Player - Ability */
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Death,"Player.Ability.Death");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light,   "Player.Ability.Attack.Light");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Charge,  "Player.Ability.Attack.Charge");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Move_Turn,      "Player.Ability.Move.Turn");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Dodge,          "Player.Ability.Dodge");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Jump,           "Player.Ability.Jump");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitReact,       "Player.Ability.HitReact");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Ability_TargetLock,     "Player.Ability.TargetLock");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Ability_FreezeTarget,   "Player.Ability.FreezeTarget");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Ability_StopAndParry,   "Player.Ability.StopAndParry");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Ability_RecoverHealth,  "Player.Ability.RecoverHealth");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Hide,           "Player.Ability.Hide");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Player_Ability_SummonMonkey,   "Player.Ability.SummonMonkey");
	
	/* Event - Ability / AnimNotify / Combat */
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Input_WaitForInput,   "Event.Input.WaitForInput");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Input_LeftClick,     "Event.Input.LeftClick");

	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Player_Turn,          "Event.Player.Turn");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Player_PerfectDodge,  "Event.Player.PerfectDodge");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Player_ParrySuccess,  "Event.Player.ParrySuccess");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Player_RecoverHealth, "Event.Player.RecoverHealth");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Player_SummonMonkey,  "Event.Player.SummonMonkey");

	/* Shared Hit Event */
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Shared_Hit,              "Event.Shared.Hit");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Shared_Hit_Melee,       "Event.Shared.Hit.Melee");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Shared_Hit_React,       "Event.Shared.Hit.React");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Shared_Hit_React_Shrink,"Event.Shared.Hit.React.Shrink");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Shared_Hit_React_Light, "Event.Shared.Hit.React.Light");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Shared_Hit_React_Heavy, "Event.Shared.Hit.React.Heavy");

	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Enemy_TD_SpawnRing,"Event.Enemy.TD.SpawnRing");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Enemy_TD_SpawnProjectile, "Event.Enemy.TD.SpawnProjectile");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Enemy_TD_SpawnImpact, "Event.Enemy.TD.SpawnImpact");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Enemy_TD_WeaponLeft,"Event.Enemy.TD.WeaponLeft");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Enemy_TD_WeaponRight,"Event.Enemy.TD.WeaponRight");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Enemy_TD_WeaponBoth,"Event.Enemy.TD.WeaponBoth");

	/* Enemy HongHaiEr Event */
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Enemy_HongHaiEr_SpawnThorn,"Event.Enemy.HongHaiEr.SpawnThorn");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Enemy_HongHaiEr_SpawnThorn_Circle,"Event.Enemy.HongHaiEr.SpawnThorn.Circle");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Enemy_HongHaiEr_SpawnThorn_Line,"Event.Enemy.HongHaiEr.SpawnThorn.Line");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Event_Enemy_HongHaiEr_SpawnProjectile, "Event.Enemy.HongHaiEr.SpawnProjectile");

	/* SetByCaller */
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(SetByCaller_Shared_BaseDamage, "SetByCaller.Shared.BaseDamage");

	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(SetByCaller_Player_AttackType,               "SetByCaller.Player.AttackType");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(SetByCaller_Player_AttackType_LigthAttack,   "SetByCaller.Player.AttackType.LightAttack");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(SetByCaller_Player_AttackType_ChargeAttack,  "SetByCaller.Player.AttackType.ChargeAttack");

	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(SetByCaller_Player_HitCount,              "SetByCaller.Player.HitCount");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(SetByCaller_Player_HitCount_LightAttack,  "SetByCaller.Player.HitCount.LightAttack");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(SetByCaller_Player_HitCount_ChargeAttack, "SetByCaller.Player.HitCount.ChargeAttack");

	/* Enemy - TD  */
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Ability,"Enemy.TD.Ability");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Ability_Attack,"Enemy.TD.Ability.Attack");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Cooldown,"Enemy.TD.Cooldown");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Cooldown_Attack,"Enemy.TD.Cooldown.Attack");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Ability_Death, "Enemy.TD.Ability.Death");
	
		/* Enemy - TD - Ability */
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Ability_Attack01, "Enemy.TD.Ability.Attack01");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Ability_Attack02, "Enemy.TD.Ability.Attack02");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Ability_Attack03, "Enemy.TD.Ability.Attack03");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Ability_Attack04, "Enemy.TD.Ability.Attack04");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Ability_Attack05, "Enemy.TD.Ability.Attack05");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Ability_Attack06, "Enemy.TD.Ability.Attack06");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Ability_Attack07, "Enemy.TD.Ability.Attack07");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Ability_Attack08, "Enemy.TD.Ability.Attack08");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Ability_Attack10, "Enemy.TD.Ability.Attack10");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Ability_Attack12, "Enemy.TD.Ability.Attack12");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Ability_Attack13, "Enemy.TD.Ability.Attack13");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Ability_HitReact, "Enemy.TD.Ability.HitReact");

	
		/* Enemy - TD - Cooldown */
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Cooldown_Attack01, "Enemy.TD.Cooldown.Attack01");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Cooldown_Attack02, "Enemy.TD.Cooldown.Attack02");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Cooldown_Attack03, "Enemy.TD.Cooldown.Attack03");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Cooldown_Attack04, "Enemy.TD.Cooldown.Attack04");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Cooldown_Attack05, "Enemy.TD.Cooldown.Attack05");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Cooldown_Attack06, "Enemy.TD.Cooldown.Attack06");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Cooldown_Attack07, "Enemy.TD.Cooldown.Attack07");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Cooldown_Attack08, "Enemy.TD.Cooldown.Attack08");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Cooldown_Attack10, "Enemy.TD.Cooldown.Attack10");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Cooldown_Attack12, "Enemy.TD.Cooldown.Attack12");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_TD_Cooldown_Attack13, "Enemy.TD.Cooldown.Attack13");

	
	/* Enemy - HongHaiEr02 */
	UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02,                 "Enemy.HongHaiEr02");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability,         "Enemy.HongHaiEr02.Ability");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack,  "Enemy.HongHaiEr02.Ability.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown,        "Enemy.HongHaiEr02.Cooldown");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack, "Enemy.HongHaiEr02.Cooldown.Attack");
	
	/* Enemy - HongHaiEr02 - Ability */
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_HitReact, "Enemy.HongHaiEr02.Ability.HitReact");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Death,         "Enemy.HongHaiEr02.Ability.Death");
	
		/* Enemy - HongHaiEr02 - Ability - Attack*/
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack01, "Enemy.HongHaiEr02.Ability.Attack.Attack01");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack02, "Enemy.HongHaiEr02.Ability.Attack.Attack02");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack03, "Enemy.HongHaiEr02.Ability.Attack.Attack03");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack04,    "Enemy.HongHaiEr02.Ability.Attack.Attack04");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack04_01, "Enemy.HongHaiEr02.Ability.Attack.Attack04.01");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack04_02, "Enemy.HongHaiEr02.Ability.Attack.Attack04.02");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack05,    "Enemy.HongHaiEr02.Ability.Attack.Attack05");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack05_01, "Enemy.HongHaiEr02.Ability.Attack.Attack05.01");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack05_02, "Enemy.HongHaiEr02.Ability.Attack.Attack05.02");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack06,    "Enemy.HongHaiEr02.Ability.Attack.Attack06");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack06_01, "Enemy.HongHaiEr02.Ability.Attack.Attack06.01");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack06_02, "Enemy.HongHaiEr02.Ability.Attack.Attack06.02");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack07, "Enemy.HongHaiEr02.Ability.Attack.Attack07");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack07_01, "Enemy.HongHaiEr02.Ability.Attack.Attack07.01");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack07_02, "Enemy.HongHaiEr02.Ability.Attack.Attack07.02");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack08,    "Enemy.HongHaiEr02.Ability.Attack.Attack08");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack08_01, "Enemy.HongHaiEr02.Ability.Attack.Attack08.01");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack08_02, "Enemy.HongHaiEr02.Ability.Attack.Attack08.02");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack09, "Enemy.HongHaiEr02.Ability.Attack.Attack09");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack10, "Enemy.HongHaiEr02.Ability.Attack.Attack10");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack11, "Enemy.HongHaiEr02.Ability.Attack.Attack11");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack12, "Enemy.HongHaiEr02.Ability.Attack.Attack12");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack13, "Enemy.HongHaiEr02.Ability.Attack.Attack13");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack14, "Enemy.HongHaiEr02.Ability.Attack.Attack14");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack15, "Enemy.HongHaiEr02.Ability.Attack.Attack15");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Ability_Attack_Attack16, "Enemy.HongHaiEr02.Ability.Attack.Attack16");


	
		/* Enemy - HongHaiEr02 - Cooldown */
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack01, "Enemy.HongHaiEr02.Cooldown.Attack.Attack01");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack02, "Enemy.HongHaiEr02.Cooldown.Attack.Attack02");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack03, "Enemy.HongHaiEr02.Cooldown.Attack.Attack03");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack04,    "Enemy.HongHaiEr02.Cooldown.Attack.Attack04");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack04_01, "Enemy.HongHaiEr02.Cooldown.Attack.Attack04.01");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack04_02, "Enemy.HongHaiEr02.Cooldown.Attack.Attack04.02");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack05,    "Enemy.HongHaiEr02.Cooldown.Attack.Attack05");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack05_01, "Enemy.HongHaiEr02.Cooldown.Attack.Attack05.01");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack05_02, "Enemy.HongHaiEr02.Cooldown.Attack.Attack05.02");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack06,    "Enemy.HongHaiEr02.Cooldown.Attack.Attack06");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack06_01, "Enemy.HongHaiEr02.Cooldown.Attack.Attack06.01");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack06_02, "Enemy.HongHaiEr02.Cooldown.Attack.Attack06.02");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack07, "Enemy.HongHaiEr02.Cooldown.Attack.Attack07");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack07_01, "Enemy.HongHaiEr02.Cooldown.Attack.Attack07.01");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack07_02, "Enemy.HongHaiEr02.Cooldown.Attack.Attack07.02");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack08,    "Enemy.HongHaiEr02.Cooldown.Attack.Attack08");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack08_01, "Enemy.HongHaiEr02.Cooldown.Attack.Attack08.01");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack08_02, "Enemy.HongHaiEr02.Cooldown.Attack.Attack08.02");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack09, "Enemy.HongHaiEr02.Cooldown.Attack.Attack09");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack10, "Enemy.HongHaiEr02.Cooldown.Attack.Attack10");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack11, "Enemy.HongHaiEr02.Cooldown.Attack.Attack11");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack12, "Enemy.HongHaiEr02.Cooldown.Attack.Attack12");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack13, "Enemy.HongHaiEr02.Cooldown.Attack.Attack13");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack14, "Enemy.HongHaiEr02.Cooldown.Attack.Attack14");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack15, "Enemy.HongHaiEr02.Cooldown.Attack.Attack15");
		WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr02_Cooldown_Attack_Attack16, "Enemy.HongHaiEr02.Cooldown.Attack.Attack16");


	/* Enemy  - Status */
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_HitReact,"Enemy.Status.HitReact");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Attacking,"Enemy.Status.Attacking");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Invincible,"Enemy.Status.Invincible");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_CantNotParry,"Enemy.Status.CantNotParry");

	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr_WeaponLeft, "Enemy.HongHaiEr.WeaponLeft");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Enemy_HongHaiEr_WeaponRight, "Enemy.HongHaiEr.WeaponRight");
	
	/* ETC */
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Clone_Ability_Attack,"Clone.Ability.Attack");
	WUKONG_API UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Death, "Shared.Status.Death");

}
