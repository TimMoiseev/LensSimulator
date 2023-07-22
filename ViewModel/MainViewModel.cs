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
        private GraphicsEngine engine;

        public string EngineState
        {
            get
            {
                if (!engine.State.IsError && engine.State.IsRunning) { return "GE Running \n"; }
                else if (engine.State.IsError) { return "Error! \n"; }
                else { return "GE Stopped \n"; }
            }
        }
        public MainViewModel() 
        {
            (engine = new()).runEngine();
            Thread.Sleep(10000);
            engine.stopEngne();

        }

        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
        }
    }
}
