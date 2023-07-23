using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace LensSimulator.Model.Graphics
{
    internal class GraphicEngineWrapper : IDisposable
    {
        [DllImport("C:\\Users\\lglgl\\Documents\\GitHub\\LensSimulator\\x64\\Debug\\GraphicsEngine.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        static protected extern IntPtr createGraphicsEngine();

        [DllImport("C:\\Users\\lglgl\\Documents\\GitHub\\LensSimulator\\x64\\Debug\\GraphicsEngine.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        static protected extern void destroyGraphicsEngine(IntPtr handle);

        [DllImport("C:\\Users\\lglgl\\Documents\\GitHub\\LensSimulator\\x64\\Debug\\GraphicsEngine.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
        static protected extern void runGraphicsEngine(IntPtr handle);

        public GraphicEngineWrapper()
        {
            wrapperHandle = createGraphicsEngine();
        }
        ~GraphicEngineWrapper()
        {
            
        }
        public void runEngine()
        {
            runGraphicsEngine(wrapperHandle);
        }

        public void Dispose()
        {
            if (wrapperHandle != IntPtr.Zero) { destroyGraphicsEngine(wrapperHandle); }
        }

        protected IntPtr wrapperHandle;
    }
}
