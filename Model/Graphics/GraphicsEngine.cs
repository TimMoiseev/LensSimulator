using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using static LensSimulator.Model.Graphics.EngineState;

namespace LensSimulator.Model.Graphics
{
    internal class GraphicsEngine
    {
        public GraphicsEngine(StateUpdateHandler eventHandler)
        {
            state.StateUpdate += eventHandler;
            
        }
        public void runEngine()
        {
            AsyncRun();
        }
        public void stopEngne()
        {
            state.IsRunning = false;
        }
        private void Run()
        {
            GraphicEngineWrapper graphicEngineWrapper = new GraphicEngineWrapper();
            graphicEngineWrapper.runEngine();
        }
        async private void AsyncRun()
        {
            await Task.Run(() => { Run(); });
        }
        public EngineState state;
        
    }
    struct EngineState 
    {
        bool isError;
        bool isRunning;
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
        public delegate void StateUpdateHandler(string message);
        public event StateUpdateHandler StateUpdate;
        public EngineState()
        {
            isRunning = false;
            isError = false;
        }
        
    }
}
