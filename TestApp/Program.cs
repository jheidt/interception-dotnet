using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using InterceptionWrapper;
using ObjectDumper;

namespace TestApp
{
    class Program
    {
        static void Main(string[] args)
        {
            using (Context c = new Context())
            {
                Console.WriteLine("setting keyboard filter");
                c.SetFilter(Context.FilterKind.KeyBoard, (ushort) (FilterKeyState.Down | FilterKeyState.Up));

                Console.WriteLine("setting mouse filter");
                c.SetFilter(Context.FilterKind.Mouse, (ushort) FilterMouseState.MOUSE_MOVE);

                Console.WriteLine("waiting on device");
                Device d = c.Wait();

                int rec = 0;
                Console.WriteLine("waiting on receive");

                while(( rec = c.Receive( (d = c.Wait() ),1)) > 0)
                {
                    Console.WriteLine("device: {0}, receive returned: {1}", d.Index, rec);
                    if(rec > 0)
                    {
                        if(d.IsKeyBoard)
                        {
                            var ks = c.GetDataAsKeyStroke();
                            Dumper.Dump(ks, "KeyStroke", Console.Out);

                            var s = c.Send(d, ks);
                            Console.WriteLine("send returned: {0}", s);

                            if(ks.code == 0x01)
                            {
                                Console.WriteLine("keystroke.code == 0x01, breaking");
                                break;
                            }
                        }
                        else if(d.IsMouse)
                        {
                            var ms = c.GetDataAsMouseStroke();
                            Dumper.Dump(ms, "MouseStroke", Console.Out);
                            var s = c.Send(d, ms);
                            Console.WriteLine("send returned: {0}", s);
                        }
                    }
                }
            }

            Console.WriteLine("press enter to continue...");
            Console.ReadLine();

            
        }
    }
}
