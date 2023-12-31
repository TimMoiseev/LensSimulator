﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Interop;
using static LensSimulator.Model.Graphics.EngineState;

namespace LensSimulator.View.SurfaceView
{
    internal class Win32SurfaceView : HwndHost
    {
        private IntPtr hwndHost;
        private IntPtr hwndChild;
        public IntPtr GetChildHandle() { return hwndChild; }
        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            hwndHost = hwndParent.Handle;
            [DllImport("C:\\Users\\lglgl\\Documents\\GitHub\\LensSimulator\\x64\\Debug\\GraphicsEngine.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi, SetLastError = true)]
            static extern bool registerSurfaceWindowClassExport();

            var result = registerSurfaceWindowClassExport();

            [DllImport("C:\\Users\\lglgl\\Documents\\GitHub\\LensSimulator\\x64\\Debug\\GraphicsEngine.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
            static extern IntPtr createSurfaceWindowExport(IntPtr hwndParrent);

            hwndChild = createSurfaceWindowExport(hwndHost);

            [DllImport("C:\\Users\\lglgl\\Documents\\GitHub\\LensSimulator\\x64\\Debug\\GraphicsEngine.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
            static extern void showSurfaceWindowExport(IntPtr hwnd);

            showSurfaceWindowExport(hwndChild);
            GetEngineState().WindowHandle = hwndChild;
            return new HandleRef(this, hwndChild);
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
            [DllImport("C:\\Users\\lglgl\\Documents\\GitHub\\LensSimulator\\x64\\Debug\\GraphicsEngine.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
            static extern void destroyWindowExport(IntPtr hwnd);
            destroyWindowExport(hwnd.Handle);
        }

        protected override IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            return base.WndProc(hwnd, msg, wParam, lParam, ref handled);
        }
    }
}
