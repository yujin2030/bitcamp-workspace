using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class App
    {
        public void init()
        {
            wbprint.logo();
           // con.fileload();
        }

        public void run()
        {
            while (true)
            {
                Console.Clear();

                //con.printall();
                wbprint.menuprint();
                switch (Console.ReadKey().Key)
                {
                    case ConsoleKey.F1: Accinsert.Invoke(); break;
                    case ConsoleKey.F2: Accprintall.Invoke(); break;
                    case ConsoleKey.F3: Accselect.Invoke(); break;
                    case ConsoleKey.F4: Accio.Invoke(true); break;
                    case ConsoleKey.F5: Accio.Invoke(false); break;
                    case ConsoleKey.F6: Accdelete.Invoke(); break;
                    case ConsoleKey.F7: Accsort.Invoke(); break;
                    case ConsoleKey.Escape: return;
                }

                wbprint.pause();
            }

        }

        public void exit()
        {
            wbprint.ending();
        }
    }
}
