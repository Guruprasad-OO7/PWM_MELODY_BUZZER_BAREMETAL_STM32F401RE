🎵 Project Title:
STM32F4 PWM Melody Player Using TIM3 and SysTick

🧠 Description
This project generates a simple melody using PWM output on an STM32F4 microcontroller (e.g., STM32F401, STM32F407) by configuring TIM3 in PWM mode. Each note's frequency and duration are defined in an array, and the waveform is played using a piezo buzzer or speaker connected to PA6 (TIM3_CH1).

🎯 Features
1.Generate musical notes with configurable frequencies and durations
2.Use TIM3 to generate PWM output at a desired frequency
3.Use SysTick for accurate millisecond delays
4.Demonstrates timer configuration, alternate function setup, and PWM modulation
5.Supports rest notes (freq = 0) for silence

🛠️ Hardware Requirements
1.Component	Notes
2.STM32F4 Development Board	Any STM32F4 series (e.g., Nucleo-F401RE)
3.Piezo buzzer / Speaker	Connect to PA6 with current limiting resistor
4.USB for power & programming	Via ST-Link or serial bootloader

📐 Pin Configuration
1.Pin	Function
2.PA6	TIM3_CH1 (PWM output)
3.Ensure PA6 is connected to your speaker or buzzer.

🧩 Software Overview
1.⏱ TIM3 Configuration (PWM Mode)
2.Prescaler (PSC): Set so timer runs at 1 MHz
3.ARR (Auto Reload Register): Adjusted based on desired frequency
4.CCR1 (Compare Register): Set to 50% of ARR for a clean square wave
⌛ SysTick Timer
Configured to generate 1ms ticks
Used for precise delays between notes
🧾 Melody Array Format
typedef struct {
    uint16_t freq;     // Frequency in Hz
    uint16_t duration; // Duration in milliseconds
} Note;
Note melody[] = {
    {262, 300},  // C4
    {294, 300},  // D4
    {330, 300},  // E4
    {0,   300}   // Rest
};

🛠️ How It Works
1.GPIO_Init:
2.Configures PA6 to use Alternate Function 2 (AF2) for TIM3.
3.TIM3_PWM_Init:
4.Enables TIM3
5.Configures PWM Mode 1 on Channel 1
6.Enables preload for ARR and CCR1
7.Starts the timer
8.SysTick_Init & delay_ms:
9.Initializes SysTick for 1ms ticks and provides millisecond delay function.
10.play_note():
11.Calculates appropriate ARR for a note frequency
12.Sets CCR1 to get 50% duty cycle
13.Restarts the timer to apply changes
14.Delays for the note’s duration

📦 How to Build and Flash
1.Open the project in STM32CubeIDE, Keil, or another STM32 toolchain.
2.Build the project.
3.Flash to your STM32F4 board.
4.Connect a buzzer/speaker to PA6.
5.Power the board and listen to the melody.

✅ Example Output
1.Notes play one after another with 50ms gaps between them.
2.A pause of 1 second is inserted before the melody repeats.

