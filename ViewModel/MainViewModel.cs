using LensSimulator.Commands;
using LensSimulator.Model.Graphics;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace LensSimulator.ViewModel
{
    internal class MainViewModel : INotifyPropertyChanged
    {
        private GraphicsEngine? engine;

        public string EngineState
        {
            get
            {
                if (engine == null) { return "GE Stopped \n"; }
                if (!engine.state.IsError && engine.state.IsRunning) { return "GE Running \n"; }
                else if (engine.state.IsError) { return "Error! \n"; }
                else { return "GE Stopped \n"; }
            }
        }
        public MainViewModel() 
        {
            
        }
        private RelayCommand? surfaceLoaded = null;
        public RelayCommand SurfaceLoaded
        {
            get 
            { return surfaceLoaded ?? (surfaceLoaded = new RelayCommand(obj => 
                {
                    engine = new(State_StateUpdate);
                    engine.runEngine();
                    engine.state.IsRunning = true;
                })); 
            }
        }

        private void State_StateUpdate(string message)
        {
            OnPropertyChanged("");
        }

        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
        }
    }
}
