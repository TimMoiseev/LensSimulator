using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace LensSimulator.Model.Graphics
{
    
    internal class MessageProcessingSystem
    {
        

        [DllImport("C:\\Users\\lglgl\\Documents\\GitHub\\LensSimulator\\x64\\Debug\\GraphicsEngine.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        static protected extern IntPtr createMessageProcessingSystem();
        [DllImport("C:\\Users\\lglgl\\Documents\\GitHub\\LensSimulator\\x64\\Debug\\GraphicsEngine.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        static protected extern void reciveMessageInternal(IntPtr target, string message);
        IntPtr handle = IntPtr.Zero;
        public MessageProcessingSystem()
        {
            handle = createMessageProcessingSystem();
        }
        public void transmitMessage(string message)
        {
            reciveMessageInternal(handle, message);
        }
    }
}
