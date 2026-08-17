# 수정 목록

## AnimInstance

### PBCharacterAnimInstance - 스레드 세이프티

- [ ] **`NativeThreadSafeUpdateAnimation`에서 외부 오브젝트 직접 접근 제거**
  - 위치: `Source/ProjectB/Private/AnimInstances/PBCharacterAnimInstance.cpp:30-31`
  - 문제: `OwningCharacter->GetVelocity()`, `OwningMovementComponent->GetCurrentAcceleration()`을
    워커 스레드에서 호출되는 `NativeThreadSafeUpdateAnimation` 안에서 직접 읽고 있음.
    게임 스레드 틱과 겹칠 경우 레이스 컨디션 가능성.
  - 해결 방향:
    1. `NativeUpdateAnimation` (게임 스레드)을 새로 오버라이드
    2. 거기서 `CachedVelocity`, `CachedAcceleration` 같은 멤버 변수로 캐시
    3. `NativeThreadSafeUpdateAnimation`은 캐시된 값만 사용해서 `GroundSpeed`, `bHasAcceleration` 계산

---

<!-- 새 카테고리/항목은 아래에 추가 -->
