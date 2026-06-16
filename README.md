# Basic Actor Control Project

내일배움캠프(NBC) 언리얼 엔진 C++ 개인 과제 3, 4 통합 프로젝트입니다.  
기본적인 회전/이동 액터 배치부터 시작하여, 엔진이 제공하는 기본 무브먼트 컴포넌트 없이 오직 C++ 코딩과 수학적 연산만으로 6축 제어 및 인공 중력을 구현한 커스텀 폰(Pawn) 프로젝트입니다.

## 📌 프로젝트 정보
- **프로젝트 이름**: P3P4
- **개발 환경**: Unreal Engine 5 (C++기반)
- **주요 목표**: Character 클래스 대신 Pawn 클래스를 사용하여 프레임 독립적인 6축 이동/회전 및 인공 물리 체계 직접 구현

---

## 🛠️ 주요 구현 기능

### 1. 액터 스폰 및 제어 (`SpawnActor`, `RotatingActor`, `MovingActor`)
- **자동 스폰 시스템**: `SpawnActor`가 시작 시 지정된 영역 내에 무작위로 회전 액터와 이동 액터를 생성합니다.
- **높이 차등 배치**: 시간의 흐름에 따른 변수 제어를 통해 공중에서 회전하는 `RotatingActor`와 지상 근처에 바짝 붙어서 이동하는 `MovingActor`의 스폰 위치(Z축)를 독립적으로 분리하였습니다.

### 2. 커스텀 폰 제어 (`OkPawn`, `OkPlayerController`)
일반적인 `ACharacter`와 달리 걷기/중력 기능이 없는 기본 `APawn`을 확장하여 기능을 구현했습니다.

* **6축 이동 (Local Based)**: 
  - 키보드 WASD(전/후/좌/우) 및 Space Bar / Left Shift(상/하) 입력을 조합한 6축 이동
  - `AddActorLocalOffset`을 활용하여 폰의 현재 회전 방향(로컬 좌표계)을 기준으로 직관적으로 이동합니다.
* **6축 회전 (Custom Rotation)**:
  - 엔진 기본 함수(`AddControllerYawInput` 등)를 배제하고 마우스 이동(Yaw, Pitch)과 휠 스크롤(Roll) 값을 직접 계산
  - `AddActorLocalRotation`과 `FMath::Clamp`를 적용하여 화면이 뒤집히지 않는 부드러운 시선 처리를 구현했습니다.
* **인공 중력 및 지면 감지 (LineTrace)**:
  - 매 프레임 발밑으로 레이저(`LineTraceSingleByChannel`)를 발사하여 지면 충돌을 수동 감지합니다.
  - **공중 상태**: 자체 중력 가속도($-980\text{ cm/s}^2$)를 적용하고 이동 속도를 40% 수준으로 제한합니다.
  - **지상 상태**: 착지하는 순간 수직 낙하 속도를 0으로 초기화하고 정상 속도로 복귀합니다.
* **모든 움직이는 사물 탑승 (Platform Ride)**:
  - 레이저에 감지된 발밑 사물의 속도(`GetVelocity()`)를 매 프레임 계산하여, 사물의 종류와 관계없이 움직이는 발판 위에 올라타면 함께 동기화되어 움직이도록 처리했습니다.

### 3. 실시간 입력 디버깅 디스플레이
- 모든 조작 키(WASD, Space, Shift, 마우스 이동, 마우스 휠)를 입력할 때마다 화면 왼쪽 상단에 어떤 키가 작동 중인지 고유한 색상의 실시간 문자열(String) 메시지로 출력되어 직관적인 피드백을 제공합니다.

---

## 🎮 조작 방법 (Input Mapping)

| 입력 장치 | 기능 | 화면 표시 문자열 |
| :--- | :--- | :--- |
| **W / S** | 전진 / 후진 (Local X) | `입력: [W] 전진` / `입력: [S] 후진` |
| **A / D** | 좌측 / 우측 이동 (Local Y) | `입력: [A] 좌측 이동` / `입력: [D] 우측 이동` |
| **Space Bar** | 점프 / 상행 (Z축 도약) | `입력: [Space] 점프 완료 (상행)` |
| **Left Shift** | 하행 (Z축 하강) | `입력: [Left Shift] 하행 중` |
| **마우스 이동** | 시선 회전 (Yaw / Pitch) | `입력: [마우스 좌/우/상/하] 시선 회전` |
| **마우스 휠** | 롤 회전 (Roll) | `입력: [마우스 휠] 위/아래로 스크롤 (Roll)` |

---

## 💡 학습 및 변경 포인트 (Character vs Pawn)

1. **프레임 독립성 보장**: 모든 이동 및 물리 연산에 `DeltaTime`을 곱해주어 프레임 속도와 무관하게 일정한 속도를 유지하도록 설계했습니다.
2. **Sweep 충돌 처리**: 물리(`Simulate Physics`)를 끈 상태에서 벽을 뚫지 않도록 `AddActorLocalOffset`의 `bSweep` 설정을 활성화했습니다.

---


https://github.com/user-attachments/assets/e785c9e7-e146-42d9-bf17-ef4d20815bd4


---
