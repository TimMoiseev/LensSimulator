using LensSimulator.Commands;
using LensSimulator.Model.Graphics;
using LensSimulator.View.OpticElement;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Text;
using System.Text.Json;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
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
            OnOffCommand offCommand = new()
            {
                CommandType = "Stop",
                Priority = 1.0f
            };
            string json_stopCommand = JsonSerializer.Serialize(offCommand);
            engine?.messageSystem?.transmitMessage(json_stopCommand);
        }

        private RelayCommand? addCommand1;
        public ICommand addCommand => addCommand1 ??= new RelayCommand(add);

        private void add(object commandParameter)
        {
            string s = "AddLensCommand";
            
            engine?.messageSystem?.transmitMessage(s);
        }

        private RelayCommand? menuBarMouseDownCommand;
        public ICommand MenuBarMouseDownCommand => menuBarMouseDownCommand ??= new RelayCommand(MenuBarMouseDown);

        private void MenuBarMouseDown(object commandParameter)
        {
            if (commandParameter != null)
            {
                if (commandParameter is MouseButtonEventArgs e)
                {
                    if (e.ChangedButton != MouseButton.Left)
                    {
                        return;
                    }

                    Grid? grid1 = e.Source as Grid;
                    Grid? grid2 = grid1?.Parent as Grid;
                    Grid? grid3 = grid2?.Parent as Grid;
                    Window? window = grid3?.Parent as Window;
                    window?.DragMove();
                }

            }
            
        }

        private RelayCommand menuBarMouseLeftButtonDownCommand;
        public ICommand MenuBarMouseLeftButtonDownCommand => menuBarMouseLeftButtonDownCommand ??= new RelayCommand(MenuBarMouseLeftButtonDown);
        private bool IsMaximized = false;
        private void MenuBarMouseLeftButtonDown(object commandParameter)
        {
            if (commandParameter != null)
            {
                if(commandParameter is MouseButtonEventArgs e)
                {
                    if(e.ClickCount == 2)
                    {
                        Grid? grid1 = e.Source as Grid;
                        Grid? grid2 = grid1?.Parent as Grid;
                        Grid? grid3 = grid2?.Parent as Grid;
                        Window? window = grid3?.Parent as Window;
                        if(window != null)
                        {
                            if (IsMaximized)
                            {
                                window.WindowState = WindowState.Normal;
                                window.Width = 1080;
                                window.Height = 720;
                                IsMaximized = false;
                            }
                            else
                            {
                                window.WindowState = WindowState.Maximized;
                                IsMaximized = true;
                            }
                        }
                        
                    }
                }
            }
        }


        private RelayCommand opticSchemeDragOverCommand1;
        public ICommand opticSchemeDragOverCommand => opticSchemeDragOverCommand1 ??= new RelayCommand(opticSchemeDragOver);

        private void opticSchemeDragOver(object commandParameter)
        {
            if (commandParameter!=null)
            {
                if (commandParameter is DragEventArgs e)
                {
                    if (e.Data.GetDataPresent("Object"))
                    {
                        if (e.KeyStates == DragDropKeyStates.ControlKey)
                        {
                            e.Effects = DragDropEffects.Copy;
                        }
                        else
                        {
                            e.Effects = DragDropEffects.Move;
                        }
                    }
                }
            }
        }

        private RelayCommand opticSchemeDropCommand1;
        public ICommand opticSchemeDropCommand => opticSchemeDropCommand1 ??= new RelayCommand(opticSchemeDrop);

        private void opticSchemeDrop(object commandParameter)
        {
            if (commandParameter != null)
            {
                if (commandParameter is DragEventArgs e)
                {
                    var sp = e.Source as StackPanel;
                    UIElement _element = (UIElement)e.Data.GetData("Object");
                    sp.Children.Add(new OpticElement((OpticElement)_element));
                }
            }
        }
    }
}
