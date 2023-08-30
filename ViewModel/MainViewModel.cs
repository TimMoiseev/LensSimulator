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
using System.Windows.Input;
using static LensSimulator.Model.Graphics.EngineState;
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
                if (!GetEngineState().IsError && GetEngineState().IsRunning) { return "GE Running \n"; }
                else if (GetEngineState().IsError) { return "Error! \n"; }
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
                    if(GetEngineState().WindowHandle != nint.Zero)
                    {
                        if(GetEngineState().IsRunning != true)
                        {
                            engine = new(State_StateUpdate);
                            engine.RunEngine();
                            GetEngineState().IsRunning = true;
                        }
                    }
                    
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

        private RelayCommand windowClosingCommand;
        public ICommand WindowClosingCommand => windowClosingCommand ??= new RelayCommand(WindowClosing);

        private void WindowClosing(object commandParameter)
        {
            engine?.StopEngine();

        }

        private RelayCommand addCommand1;
        public ICommand addCommand => addCommand1 ??= new RelayCommand(add);

        private void add(object commandParameter)
        {
            string s = "AddLensCommand";
            engine.messageSystem.transmitMessage(s);
        }
    }
}
