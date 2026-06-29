# Wukong — 3인칭 액션 게임 (보스 전투 데모)

> 블랙 신화: 오공을 레퍼런스로 제작한 언리얼 엔진 5 기반 3인칭 액션 게임입니다.  
> GAS(Gameplay Ability System)를 활용해 플레이어 전투, 에너미 AI, 카메라 시스템을 C++로 구현했습니다.

---

## 🛠 사용 기술

| 분류 | 내용 |
|------|------|
| **Engine** | Unreal Engine 5 |
| **Language** | C++ |
| **Combat** | GAS (Gameplay Ability System) — AbilitySystemComponent, AttributeSet, GameplayEffect, ExecutionCalculation |
| **Input** | Enhanced Input System |
| **AI** | Behavior Tree, Blackboard, AI Perception System |
| **FX** | Niagara, Motion Warping |

---

## 📁 프로젝트 구조

```
Source/Wukong/
├── Private/
│   ├── AbilitySystem/
│   │   ├── Ability/
│   │   │   ├── WK_GameplayAbility              어빌리티 베이스 (입력 릴리즈 처리)
│   │   │   ├── WK_PlayerGameplayAbility         플레이어 어빌리티 베이스 (컴포넌트 접근, 이펙트 스펙 빌더)
│   │   │   ├── WK_EnemyGameplayAbility          에너미 어빌리티 베이스
│   │   │   ├── WK_PlayerSummonMonkeyAbility     분신 소환 어빌리티
│   │   │   ├── WK_EnemySummonAbility            에너미 소환 어빌리티
│   │   │   └── WK_PlayerAbilityTargetLock       타겟 락온 어빌리티
│   │   ├── AbilityTask/
│   │   │   └── AbilityTask_ExecuteOnTick        틱 기반 커스텀 어빌리티 태스크
│   │   ├── BTService/
│   │   │   ├── BTService_SelectNextAttack       공간 분석 기반 공격 선택 태스크
│   │   │   ├── BTService_OrientToTarget         타겟 방향 보간 회전 서비스
│   │   │   └── BTTask_RotateFaceToTarget        공격 전 정면 정렬 태스크
│   │   ├── GEExecCalc/
│   │   │   └── GEExecCalc_Damage               데미지 최종 계산 (콤보·차지·다단히트 반영)
│   │   ├── WK_AbilitySystemComponent            커스텀 ASC (콤보 입력 사전 분기)
│   │   └── WK_AttributeSet                     13개 속성 & 후처리 (게이지·스태미나·사망)
│   ├── Actions/
│   │   ├── WK_AsyncTaskCooldownChanged          비동기 쿨다운 트래킹 (멀티 태그 리스닝)
│   │   └── WK_CoolDownTimer                    커스텀 레이턴트 쿨다운 타이머
│   ├── Actor/
│   │   ├── WK_ProjectileBase                   투사체 (직선 / 호밍 / 지면스냅 / 호밍+지면스냅)
│   │   └── WK_AreaActorBase                    확장형 링 AOE (반지름 증가·도넛 판정)
│   ├── Animation/AnimNotify/
│   │   ├── WK_ANS_InputWindow                  콤보 입력 윈도우 열기/닫기
│   │   ├── WK_ANS_TagManager                   애니메이션 구간별 GAS 태그 추가·제거 / 이동속도 제어
│   │   └── ANS_UpdateActorRotation             애니메이션 중 블랙보드 타겟 방향 보간 회전
│   ├── Character/
│   │   ├── WK_BaseCharacter                    공통 베이스 (ASC, AttributeSet, MotionWarping)
│   │   ├── WK_PlayerCharacter                  플레이어 (궤도 이동 블렌딩, Enhanced Input 바인딩)
│   │   ├── WK_EnemyCharacter                   에너미 (사지별 콜리전 4개, 오디오)
│   │   ├── WK_PlayerCloneCharacter             분신 클론 (AI 제어, 독립 ASC)
│   │   └── Component/
│   │       ├── WK_PawnComponentBase            컴포넌트 베이스
│   │       ├── Combat/
│   │       │   ├── WK_PawnCombatComponent      히트 중복 방지, 콜리전 토글 베이스
│   │       │   ├── WK_PlayerCombatComponent    소켓 기반 동적 캡슐 트랜스폼
│   │       │   ├── WK_EnemyCombatComponent     사지별(4개) 독립 캡슐 관리
│   │       │   ├── Combo/
│   │       │   │   └── WK_PlayerComboComponent 콤보 인덱스·차지 게이지·닷지 방향 관리
│   │       │   └── TargetLock/
│   │       │       └── WK_PlayerTargetLockComponent  락온 (구체 탐색·카메라·몸통·위젯)
│   │       └── UI/
│   │           ├── WK_PawnUIComponent          체력 델리게이트 베이스
│   │           ├── WK_PlayerUIComponent        마나·스태미나·게이지·물약 델리게이트
│   │           └── WK_EnemyUIComponent         에너미 체력바 위젯 관리
│   ├── Controller/
│   │   ├── WK_PlayerController                 팀 ID 0 설정
│   │   ├── WK_EnemyController                  AI 퍼셉션 (시야 5000u, 360°) & 팀 적대 판정
│   │   └── WK_PlayerCloneController            클론 AI (CrowdFollowing, 장애물 회피)
│   ├── Data/
│   │   ├── WK_StartUpAbilities                 어빌리티·이펙트 초기 부여 베이스
│   │   ├── WK_PlayerStartUpAbilities           플레이어 어빌리티 + 입력 태그 등록
│   │   ├── WK_EnemyStartUpAbilities            에너미 어빌리티 등록
│   │   ├── WK_EnemyAttackPool                  에너미별 공격 풀 데이터 에셋
│   │   └── WK_InputDataConfig                  Enhanced Input 액션·매핑 컨텍스트 설정
│   ├── Input/
│   │   └── WK_EnhancedInputComponent           어빌리티 입력 바인딩 래퍼
│   ├── Interface/
│   │   ├── WK_PawnCombatInterface              전투 컴포넌트 접근 인터페이스
│   │   └── WK_PawnUIInterface                  UI 컴포넌트 접근 인터페이스
│   ├── Widgets/
│   │   └── WK_WidgetBase                       UMG 위젯 베이스
│   ├── WK_BlueprintFunctionLibrary             태그 관리·방향 계산·거리 판정·이펙트 적용 유틸
│   └── WK_GameplayTags                         게임 전체 태그 100+ 정의
└── Public/
    └── Types/
        ├── WK_EnumTypes                        EActorDirection 등 공용 열거형
        └── WK_StructTypes                      FActorDodgeAbility, FWeaponCollisionCachedData 등
```

---

## ⚙️ 핵심 구현

---

### 1. 타겟 락온 시스템

락온 활성화 시 **이동 / 카메라 / UI 위젯** 세 가지를 독립적으로 제어합니다.

#### 이동 — 궤도 공전 블렌딩

적과의 거리가 `AcceptRadius` 이하로 좁혀지면, 직선 이동을 줄이고 원형 공전 이동 비중을 높입니다.  
내적(Dot Product)으로 카메라 전방과 공전 접선을 비교해 공전 방향(좌/우)을 결정하고,  
거리 비율을 Alpha로 변환해 두 벡터를 **Lerp로 블렌딩**합니다.

```cpp
// WK_PlayerCharacter.cpp — Input_Move()

FVector OrbitLeft  = FVector::CrossProduct(DirToTarget, FVector::UpVector);
FVector OrbitRight = -OrbitLeft;

// 카메라 전방과 공전 접선을 내적 비교해 공전 방향 결정
FVector OrbitDir = (FVector::DotProduct(ForwardDirection, OrbitLeft) >
                    FVector::DotProduct(ForwardDirection, OrbitRight))
                    ? OrbitLeft : OrbitRight;

// 거리가 가까울수록 Alpha → 1 (완전 공전), 멀수록 Alpha → 0 (직선)
float Alpha = FMath::Clamp((OrbitRadius - Distance) / 150.0f, 0.0f, 1.0f);
ForwardDirection = FMath::Lerp(ForwardDirection, OrbitDir, Alpha).GetSafeNormal();
```

#### 카메라 — 부드러운 추적 + 피치 클램핑

```cpp
// WK_PlayerTargetLockComponent.cpp — UpdateCameraRotation()

FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 5.0f);
SmoothRotation.Pitch = FMath::Clamp(SmoothRotation.Pitch, -40.0f, 5.f); // 카메라가 땅을 뚫지 않도록 클램핑
OwnerController->SetControlRotation(SmoothRotation);
```

#### 캐릭터 회전 — 상태 기반 전환

스프린트·패리 중에는 `bOrientRotationToMovement`를 복원해 자연스러운 이동 방향 회전으로 전환합니다.

```cpp
// WK_PlayerTargetLockComponent.cpp — UpdatePlayerRotation()

if (bIsParry || bIsSprinting || InputVector.IsZero())
{
    Owner->GetCharacterMovement()->bOrientRotationToMovement = true; // 이동 방향으로 회전 복원
    return;
}
FRotator SmoothRot = FMath::RInterpConstantTo(CurrentRot, LookAtRot, DeltaTime, 250.f);
Owner->SetActorRotation(SmoothRot);
```

#### UI 위젯 — 화면 공간 동기화

매 프레임 타겟 스켈레톤의 `TargetLockSocket` 위치를 화면 좌표로 변환하고,  
위젯 크기 절반을 빼서 중앙 정렬합니다.

```cpp
// WK_PlayerTargetLockComponent.cpp — SetWidgetLocation()

UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
    OwnerController, TargetWorldLocation, ScreenPosition, true);

ScreenPosition -= WidgetSize / 2.f;
TargetLockWidget->SetPositionInViewport(ScreenPosition, false);
```

---

### 2. 동적 무기 콜리전

애니메이션 재생 중 **무기 스윙 궤적에 맞게 캡슐 콜리전을 매 프레임 재계산**합니다.  
정적 히트박스는 빠른 스윙 애니메이션에서 히트 미스가 발생하는 문제를 해결하기 위해 구현했습니다.

#### 플레이어 — 소켓 기반 캡슐 트랜스폼 계산

```cpp
// WK_PlayerCombatComponent.cpp — UpdateCollision()

const FVector WeaponVector   = WeaponStartLocation - WeaponEndLocation;
const FVector WeaponCenter   = (WeaponStartLocation + WeaponEndLocation) / 2.f;

// 무기 벡터 방향으로 캡슐 회전 정렬
const FQuat CapsuleRotation  = FRotationMatrix::MakeFromZ(WeaponVector.GetSafeNormal()).ToQuat();

// 무기 길이 절반 = 캡슐 HalfHeight (자동 크기 조정)
const float CapsuleHalfHeight = WeaponVector.Size() * 0.5f;

Capsule->SetWorldLocation(WeaponCenter);
Capsule->SetWorldRotation(CapsuleRotation);
Capsule->SetCapsuleHalfHeight(CapsuleHalfHeight);
```

#### 에너미 — 사지별 독립 콜리전

왼손 / 오른손 / 왼발 / 오른발 **4개의 캡슐을 독립 관리**합니다.  
공격 종류에 따라 블루프린트에서 활성화할 사지를 지정합니다.

#### 히트 중복 방지

`OverlappedActors` 배열로 한 스윙 안에서 동일 액터에 데미지가 두 번 들어가지 않도록 합니다.  
콜리전 비활성화 시 배열을 초기화합니다.

---

### 3. GAS 데미지 파이프라인

**어빌리티 → GameplayEffect → ExecutionCalculation** 단방향 파이프라인으로  
데미지 계산 로직을 `GEExecCalc_Damage` 한 곳에서 관리합니다.

#### SetByCaller로 데이터 주입

어빌리티에서 GameplayEffect에 값을 태그로 주입합니다.

| 태그 | 역할 |
|------|------|
| `SetByCaller_Shared_BaseDamage` | 기본 공격력 |
| `SetByCaller_Player_AttackType_LightAttack` | 현재 콤보 단계 |
| `SetByCaller_Player_AttackType_ChargeAttack` | 차지 레벨 |
| `SetByCaller_Player_HitCount` | 다단히트 횟수 |

#### ExecutionCalculation 공식

```cpp
// GEExecCalc_Damage.cpp

// 라이트 콤보 보너스: 콤보가 쌓일수록 20%씩 증가
if (LightAttackComboCount > -1.f)
    Damage *= (LightAttackComboCount * 0.2f + 1.0f);

// 차지 보너스: 차지 레벨당 50% 증가
if (ChargeAttackComboCount > -1.f)
    Damage *= (ChargeAttackComboCount * 0.5f + 1.0f);

// 다단히트 분산: 총 데미지를 히트 횟수로 나눔
if (MaxHitCount > 0.f)
    Damage *= (1.f / MaxHitCount);

// 최종 데미지
float TotalDamage = SourceAttackPower * Damage / TargetDefensePower;
```

> 방어력은 스냅샷 없이 실행 시점의 실제 값을 사용해 버프·디버프가 즉시 반영됩니다.

---

### 4. AttributeSet 기반 상태 관리

`PostGameplayEffectExecute` 한 곳에서 수치 변화의 **모든 후처리**를 담당합니다.

#### 게이지 → 차지 포인트 전환

`CurrentGauge`가 `MaxGauge`에 도달하면 게이지를 0으로 리셋하고  
`ChargedAttackComboIndex`를 1 증가시킵니다. (최대 3단계)  
동시에 무기 이펙트 스케일을 키워 시각적 피드백을 제공합니다.

```cpp
// WK_AttributeSet.cpp

if (GetCurrentGauge() == GetMaxGauge())
{
    SetCurrentGauge(0.f);                                            // 게이지 리셋
    PlayerComboComponent->SetCurrentChargedAttackComboIndex(ChargedCombo + 1); // 차지 단계 증가
    PlayerUIComponent->OnGaugePointChanged.Broadcast(ChargedCombo + 1);        // UI 업데이트
    PlayerComboComponent->OnWeaponGaugeMax();                        // 무기 이펙트 확장
}
```

#### 스태미나 → 태그 자동 동기화

스태미나가 0이 되면 `Player_Status_NoStamina` 태그를 추가해  
닷지·스프린트 어빌리티 활성화를 자동으로 차단합니다.

#### UI 인터페이스 캐싱

`TWeakInterfacePtr`로 UI 컴포넌트를 **최초 1회만 캐싱**해 반복 캐스팅 비용을 제거합니다.

```cpp
if (CachedPawnUIInterface == nullptr)
    CachedPawnUIInterface = TWeakInterfacePtr<IWK_PawnUIInterface>(Data.Target.GetAvatarActor());
```

---

### 5. AI 공격 선택 (BTTask)

비헤이비어 트리 태스크에서 **플레이어의 공간적 위치를 분석해** 적절한 공격을 선택합니다.

```cpp
// BTService_SelectNextAttack.cpp

const float ForwardDot = FVector::DotProduct(F2, D);
const bool InBack = (ForwardDot < BehindDegree); // 전방 내적 < 0.4 → 등 뒤 120도 판정

const float CrossZ = FVector::CrossProduct(F2, D).Z;
const bool InLeft  = (CrossZ < -0.02f);          // 외적 Z 부호 → 좌/우 판별
```

| 조건 | 선택 공격 |
|------|----------|
| 등 뒤 + 왼쪽 | Attack06 (왼쪽 등 뒤 전용) 즉시 선택 |
| 등 뒤 + 오른쪽 | Attack07 (오른쪽 등 뒤 전용) 즉시 선택 |
| 그 외 | 거리 범위 + 쿨다운 태그 필터 후 랜덤 선택 |

에너미별 공격 목록은 `UWK_EnemyAttackPool` 데이터 에셋으로 분리해  
코드 수정 없이 에디터에서 각 에너미의 공격 셋을 구성할 수 있습니다.

---

## 트러블슈팅 / 기술적 결정

| 문제 | 해결 |
|------|------|
| 빠른 스윙 애니메이션에서 히트박스 미스 | 소켓 2개 기반 동적 캡슐 트랜스폼 계산 |
| 락온 중 적에 붙으면 이동 막힘 | 거리 비율 Alpha로 직진↔공전 블렌딩 |
| 콤보 입력이 GAS 어빌리티 타이밍과 충돌 | ASC에서 콤보 입력을 사전 분기해 ComboComponent로 라우팅 |
| AttributeSet 후처리 시 반복 인터페이스 캐스팅 | TWeakInterfacePtr 최초 1회 캐싱 |
| 에너미 퍼셉션 노이즈로 타겟 갱신 반복 | 타겟이 없을 때만 설정, 해제는 BT에서 담당 |
