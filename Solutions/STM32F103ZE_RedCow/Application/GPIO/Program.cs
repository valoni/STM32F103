using System;
using Microsoft.SPOT;
using Microsoft.SPOT.Hardware;
using System.Threading;

namespace GPIO
{
    public class Program
    {
        //The GPIO_Pin pass to the GPIO driver is base on 0 and end with (CPU_GPIO_GetPinCount() - 1).
        //So I use the index map to the stm32f10x pin
        enum STM32F10X_GPIO
        {
            PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13, PA14, PA15,
            PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13, PB14, PB15,
            PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7, PC8, PC9, PC10, PC11, PC12, PC13, PC14, PC15,
            PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7, PD8, PD9, PD10, PD11, PD12, PD13, PD14, PD15,
            PE0, PE1, PE2, PE3, PE4, PE5, PE6, PE7, PE8, PE9, PE10, PE11, PE12, PE13, PE14, PE15,
            PF0, PF1, PF2, PF3, PF4, PF5, PF6, PF7, PF8, PF9, PF10, PF11, PF12, PF13, PF14, PF15,
            PG0, PG1, PG2, PG3, PG4, PG5, PG6, PG7, PG8, PG9, PG10, PG11, PG12, PG13, PG14, PG15,
        };

        //The LED in the RedCow board
        enum LED
        {
            D1 = STM32F10X_GPIO.PF6,
            D2 = STM32F10X_GPIO.PF7,
            D3 = STM32F10X_GPIO.PF8,
            D4 = STM32F10X_GPIO.PF9,
            D5 = STM32F10X_GPIO.PF10,
        };

        //The button in the RedCow board
        enum BUTTON
        { 
            USER1 = STM32F10X_GPIO.PA8,
            USER2 = STM32F10X_GPIO.PD3,
            WAKEUP = STM32F10X_GPIO.PA0,
            TAMPER = STM32F10X_GPIO.PC13,
        };

        //---------------------------------------------------
        //Description
        //  The applicaiton entry point
        //---------------------------------------------------
        public static void Main()
        {
            //The button pin
            Cpu.Pin[] Button_Pins = new Cpu.Pin[]{(Cpu.Pin)BUTTON.USER1, (Cpu.Pin)BUTTON.USER2, (Cpu.Pin)BUTTON.WAKEUP, (Cpu.Pin)BUTTON.TAMPER};

            //The led pin
            Cpu.Pin[] Led_Pins = new Cpu.Pin[] { (Cpu.Pin)LED.D1, (Cpu.Pin)LED.D2, (Cpu.Pin)LED.D3, (Cpu.Pin)LED.D4, (Cpu.Pin) LED.D5};

            //Attach the interrupt port to the button
            InterruptPort[] Button = new InterruptPort[Button_Pins.Length];
            for (int i = 0; i < Button.Length; i++)
            {
                //Create a new port for interrupt
                Button[i] = new InterruptPort(Button_Pins[i], false, Port.ResistorMode.PullDown, Port.InterruptMode.InterruptEdgeBoth);
                
                //Attach the handler function to the button
                Button[i].OnInterrupt += new NativeEventHandler(InterruptHandler);
            }

            //Initialize the output pin for LED
            OutputPort[] Led = new OutputPort[Led_Pins.Length];
            for (int i = 0; i < Led.Length; i++)
            {
                Led[i] = new OutputPort(Led_Pins[i], false);
            }

            while (true)
            {
                foreach (OutputPort led in Led)
                {
                    //Flicker
                    led.Write(!led.Read());           
                }
                Thread.Sleep(10000);
                
            }
        }

        //---------------------------------------------------
        //Description
        //  The interrupt handler funtion
        //---------------------------------------------------
        static void InterruptHandler(uint data1, uint data2, DateTime time)
        {
            //Convert to the BUTTON enumerate value
            BUTTON btn = (BUTTON)data1;

            if (data2 == 0)
            {
                //Pop
                Debug.Print(btn.ToString() + ":Pop");
            }
            else
            { 
                //Push
                Debug.Print(btn.ToString() + ":Push");
            }
        }

    }
}
