﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading;
using System.Threading.Tasks;
using static LensSimulator.Model.Graphics.EngineState;

namespace LensSimulator.Model.Graphics
{   
    internal class GraphicsEngine
    {
        public GraphicsEngine(StateUpdateHandler eventHandler)
        {
            messageSystem = MessageProcessingSystem.getSystem();
            GetEngineState().StateUpdate += eventHandler;
            
        }
        public void RunEngine()
        {
            AsyncRun();
        }
        public void StopEngine()
        {
            GetEngineState().IsRunning = false;
            graphicEngineWrapper?.Dispose();
        }
        
        async private void AsyncRun()
        {
            await Task.Run(() => {
                graphicEngineWrapper = new GraphicEngineWrapper();
                
                graphicEngineWrapper.runEngine();});
            System.Windows.Application.Current.Shutdown();
        }
        
        private GraphicEngineWrapper? graphicEngineWrapper;
        public MessageProcessingSystem? messageSystem;
    }
    public sealed class EngineState 
    {
        private static EngineState? state;
        bool isError;
        bool isRunning;
        bool windowCreated;
        IntPtr windowHandle;
        public bool IsRunning
        {
            get { return isRunning; }
            set 
            { 
                isRunning = value;
                StateUpdate?.Invoke("IsRunning");
            }
        }
        public bool IsError
        {
            get { return isError; }
            set 
            { 
                isError = value;
                StateUpdate?.Invoke("IsError");
            }
        }
        public IntPtr WindowHandle
        {
            get { return windowHandle; }
            set 
            { 
                windowHandle = value; 
                windowCreated = true;
                StateUpdate?.Invoke("WindowHandle");
            }
        }
        public delegate void StateUpdateHandler(string message);
        public event StateUpdateHandler? StateUpdate;
        public static EngineState GetEngineState()
        {
            if(state == null) { state  = new EngineState(); return state; }
            else { return state; }
        }
        private EngineState()
        {
            isRunning = false;
            isError = false;
        }
        
    }
}
