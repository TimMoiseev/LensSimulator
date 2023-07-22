using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace LensSimulator.Model.Graphics
{
    internal class GraphicsEngine
    {
        public void runEngine()
        {
            state.IsRunning = true;
            state.IsError = false;
        }
        public void stopEngne()
        {
            state.IsRunning = false;
        }
        private EngineState state;
        public EngineState State { get { return state; } set { } }
        
    }
    struct EngineState : INotifyPropertyChanged
    {
        bool isError;
        bool isRunning;
        public bool IsRunning
        {
            get { return isRunning; }
            set 
            { 
                isRunning = value;
                OnPropertyChanged();
            }
        }
        public bool IsError
        {
            get { return isError; }
            set 
            { 
                isError = value;
                OnPropertyChanged();
            }
        }
        public EngineState()
        {
            isRunning = false;
            isError = false;
        }
        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            if (PropertyChanged != null && !IsError)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
            }
        }
    }
}
