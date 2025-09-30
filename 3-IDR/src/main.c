#include "stm32f4xx_hal.h"  // Se usó HAL porque sin esto no se pueden usar las funciones para manejar los pines y los relojes

// Prototipos de funciones 
void SystemClock_Config(void);   // Esta es para el reloj principal del micro
static void MX_GPIO_Init(void);  // Esta es para inicializar los pines (LED y botón)

int main(void)
{
  HAL_Init();              // Se inicializa todo lo básico de la HAL
  SystemClock_Config();    // Se llama a la función que me configura el reloj del sistema
  MX_GPIO_Init();          // Se preparan los pines que voy a usar: PA5 como salida y PC13 como entrada

  while (1)   
  {
    // Acá se lee el pin del botón en PC13
    // En esta placa cuando aprieto el botón baja a 0, y cuando lo suelto se va a 1
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
    {
      // Si detecta que el botón está presionado, entonces aquí manda un 1 a PA5 para encender el LED
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    }
    else
    {
      // Y si el botón no está presionado, aquí manda un 0 a PA5 para apagar el LED
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    }
  }
}

// Configuración del reloj del sistema
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};  // Aquí declaré la estructura para configurar el oscilador
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};  // Y esta para los clocks principales

  __HAL_RCC_PWR_CLK_ENABLE();                        // Aquí habilité el reloj del controlador de energía
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2); // Aca se ajusta el regulador de voltaje

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;    // Decidí usar el oscilador interno HSI
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                      // Aquí lo activé
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT; // Dejé la calibración por defecto
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;                  // Prendí el PLL para multiplicar la frecuencia
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;          // Puse el HSI como fuente del PLL
  RCC_OscInitStruct.PLL.PLLM = 16;                              // Aquí configuré el divisor M
  RCC_OscInitStruct.PLL.PLLN = 336;                             // Aquí configuré el multiplicador N
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;                   // Aquí seleccioné la división P
  RCC_OscInitStruct.PLL.PLLQ = 7;                               // Y aquí el divisor Q
  HAL_RCC_OscConfig(&RCC_OscInitStruct);                        // Con esta línea apliqué toda esa config

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2; // Aquí seleccioné qué relojes voy a configurar
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;     // El sistema va a usar el PLL como fuente
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;            // Dejé el bus AHB sin división
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;             // El APB1 sí lo dividí entre 2
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;             // El APB2 lo dejé igual
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);     // Aquí ya terminé de configurar los relojes
}

// Inicialización de pines GPIO
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};  // Aquí declaré la estructura para configurar los pines

  __HAL_RCC_GPIOA_CLK_ENABLE();  // Activé el reloj del puerto A (porque ahí está el LED)
  __HAL_RCC_GPIOC_CLK_ENABLE();  // Activé el reloj del puerto C (porque ahí está el botón)

  // Configuracion del pin PA5 como salida push-pull para manejar el LED
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;   // Lo puse en modo salida
  GPIO_InitStruct.Pull = GPIO_NOPULL;           // No usé resistencias pull-up ni pull-down
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  // Lo dejé en velocidad baja (me basta para un LED)
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);       // Apliqué la configuración al puerto A

  
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;       // Lo puse como entrada
  GPIO_InitStruct.Pull = GPIO_NOPULL;           // No puse pull-up ni pull-down, la placa ya trae su lógica
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);       // Apliqué la configuración al puerto C
}

/*
========================================================================================
INSTRUCCIONES PARA PROBARLO EN FÍSICO:

1. Abrir STM32CubeIDE y crear un nuevo proyecto seleccionando la placa Nucleo-F446RE.
2. En el configurador CubeMX activar el pin PA5 como "GPIO_Output" y el pin PC13 como "GPIO_Input".
3. Generar el código base del proyecto.
4. Reemplazar el contenido del archivo main.c por el código mostrado arriba.
5. Compilar el proyecto y grabarlo en la placa usando la opción "Run".
6. Con la placa encendida, presionar el botón azul USER (conectado a PC13).
7. Observar que mientras el botón está presionado, el LED verde LD2 (conectado a PA5) se enciende.
8. Al soltar el botón, verificar que el LED se apaga.

De esta manera se confirma que el microcontrolador detecta el estado del botón y controla el LED en tiempo real.
========================================================================================
*/
