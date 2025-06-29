# FreeRTOS_Elavator_Project
Board: STM32
### 📌 프로젝트 개요

| 항목 | 내용 |
| --- | --- |
| 프로젝트명 | RTOS 기반 멀티태스킹 엘리베이터 시스템 |
| 개발 환경 | STM32 + FreeRTOS |
| 사용 언어 | C |
| 주요 기능 | 멀티태스킹 제어, 층 선택, 스텝모터 제어, 도트매트릭스 디스플레이, 포토센서 감지 |
| 역할 | Task 설계, Queue 처리, 공유 자원 보호(Mutex), 스텝모터 및 디스플레이 연동 |
📁 Links
📗 블로그 설명 글

🧪 Github Repo

yaml
복사
편집

---

## 🛗 4. `FreeRTOS_Elevator_Project`

```markdown
# 🛗 Elevator System – RTOS 기반 실시간 제어 프로젝트

A multi-tasking elevator controller using **FreeRTOS on STM32**, integrating FSM, step motor, dot matrix, and photo sensor.

---

## ⚙️ Components

| Module     | Description                        |
|------------|------------------------------------|
| MCU        | STM32F407 / STM32CubeIDE           |
| OS         | FreeRTOS                           |
| Motor      | Step Motor + Driver                |
| Sensor     | Photo interrupter for floor detect |
| Display    | Dot Matrix, FND                    |
| Language   | C (FreeRTOS HAL)                   |

---

## 🧠 Task Structure

| Task Name        | Function                       |
|------------------|--------------------------------|
| TaskDefault      | Display & Mutex-protected log  |
| TaskFSMControl   | Elevator FSM & queue handling  |
| TaskMotorControl | Step Motor move                |
| TaskBuzzer       | Floor arrival sound            |

---

## 🔄 FSM Logic

```txt
Idle → Move → Stop at floor → Wait → Next request
end_floors[] 배열 기반 예약 큐

층별 요청 처리 → 방향 전환 + 출력

🔧 RTOS Resource Use
Queue: 층 예약 요청 처리

Semaphore: 센서 감지 동기화

Mutex: 디스플레이 자원 보호

▶️ Run & Build
STM32CubeIDE → FreeRTOS 설치

각 Task 정의 후 Build → Flash

UART로 디버깅 로그 출력 확인
