using LensSimulator.Commands;
using LensSimulator.Model.Graphics;
using LensSimulator.Model.Lens;
using LensSimulator.View.OpticElement;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
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
using static LensSimulator.Model.Graphics.MessageProcessingSystem;
namespace LensSimulator.ViewModel
{
    internal class MainViewModel : INotifyPropertyChanged
    {
        private LensView? _currentLens = null;
        public LensView? CurrentLens { 
            get { return _currentLens; } 
            set { _currentLens = value; OnPropertyChanged(nameof(CurrentLens)); } 
        }
        private ObservableCollection<LensModel> _lensesModels = new();
        public ObservableCollection<LensModel> LensesModels {
            get { return _lensesModels; }
            set { _lensesModels = value;}
        }
        private ObservableCollection<LensView> _lensesViews = new();
        public ObservableCollection<LensView> LensesViews
        {
            get { return _lensesViews; }
            set { _lensesViews = value;}
        }

        private void CreateLensesViewsFromLensesModels(ObservableCollection<LensView> views, IEnumerable<LensModel> models)
        {
            foreach (var model in models)
            {
                views.Add(LensViewFromLensModel(model));
            }
        }
        private LensView LensViewFromLensModel(LensModel model)
        {
             return new LensView()
             {
                 Id = model.Id,
                 R1 = model.R1,
                 R2 = model.R2,
                 D = model.D,
                 H = model.H,
                 X = model.X,
                 Y = model.Y,
                 Z = model.Z
             };
        }
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
            LensesModels.CollectionChanged += LensesModelsCollectionChanged;
            LensesViews.CollectionChanged += LensViewCollectionChanged;
        }

        private void LensViewCollectionChanged(object? sender, NotifyCollectionChangedEventArgs e)
        {
            OnPropertyChanged(nameof(LensesViews));
            if (e.NewItems != null) {
                foreach (LensView newView in e.NewItems)
                {
                    newView.PropertyChanged += LensView_PropertyChanged;
                }
            }
            if(e.OldItems != null)
            {
                foreach (LensView oldView in e.OldItems)
                {
                    oldView.PropertyChanged -= LensView_PropertyChanged;
                }
            }
            
        }

        private void LensesModelsCollectionChanged(object? sender, NotifyCollectionChangedEventArgs e)
        {
            if(e.NewItems != null)
            {
                foreach (LensModel newModel in e.NewItems) {
                    
                    LensesViews.Add(LensViewFromLensModel(newModel));
                    newModel.PropertyChanged += LensModel_PropertyChanged;
                    MessageProcessingSystem MessageSystem = MessageProcessingSystem.getSystem();
                    ChangeLensModelIn3DViewport(newModel, ChangeLensMessageType.Add);
                }
            }
            if(e.OldItems != null)
            {
                foreach(LensModel oldModel in e.OldItems)
                {
                    LensesViews.Remove(LensViewFromLensModel(oldModel));
                    oldModel.PropertyChanged -= LensModel_PropertyChanged;
                    
                }
            }
        }

        private void LensModel_PropertyChanged(object? sender, PropertyChangedEventArgs e)
        {
            if(sender != null)
            {
                var model = sender as LensModel;
                var propertyName = e.PropertyName;
                if(propertyName == nameof(LensModel.X) || propertyName == nameof(LensModel.Y) || propertyName == nameof(LensModel.Z))
                {
                    ChangeLensModelIn3DViewport(model, ChangeLensMessageType.Move);
                }
                else
                {
                    ChangeLensModelIn3DViewport(model, ChangeLensMessageType.Change);
                }
                
                
            }
        }
        private void LensView_PropertyChanged(object? sender, PropertyChangedEventArgs e)
        {
            if(sender != null)
            {
                LensView lv = sender as LensView;
                var foundModel = LensesModels.FirstOrDefault(item => item.Id == lv.Id);
                if (foundModel.D != lv.D) { foundModel.D = lv.D; };
                if (foundModel.R1 != lv.R1) { foundModel.R1 = lv.R1; };
                if (foundModel.R2 != lv.R2) { foundModel.R2 = lv.R2; };
                if (foundModel.H != lv.H) { foundModel.H = lv.H; };
                if (foundModel.X != lv.X) { foundModel.X = lv.X; };
                if (foundModel.Y != lv.Y) { foundModel.Y = lv.Y; };
                if (foundModel.Z != lv.Z) { foundModel.Z = lv.Z; };
            }
            
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
            OnPropertyChanged(message);
        }

        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));
        }

        private RelayCommand windowClosingCommand;
        public ICommand WindowClosingCommand => windowClosingCommand ??= new RelayCommand(WindowClosing);

        private void WindowClosing(object commandParameter)
        {
            MessageProcessingSystem.OnOffCommand offCommand = new()
            {
                CommandType = "Stop",
                Priority = 1.0f
            };
            string json_stopCommand = JsonSerializer.Serialize(offCommand);
            engine?.messageSystem?.transmitMessage(json_stopCommand);
        }
        private static void ChangeLensModelIn3DViewport(LensModel model, ChangeLensMessageType messageType)
        {
            MessageProcessingSystem.ChangeLensMessage message =
                new()
                {
                    MessageType = messageType,
                    ID = model.Id,
                    LensType = model.LensType,
                    D = (float)model.D,
                    R1 = (float)model.R1,
                    R2 = (float)model.R2,
                    H = (float)model.H,
                    X = (float)model.X,
                    Y = (float)model.Y,
                    Z = (float)model.Z
                    
                };
            MessageProcessingSystem system = MessageProcessingSystem.getSystem();
            string addLensJson = JsonSerializer.Serialize(message);
            system.transmitMessage(addLensJson);
            
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

    }
}
