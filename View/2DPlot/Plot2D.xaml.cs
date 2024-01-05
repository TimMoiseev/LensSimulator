using LensSimulator.Commands;
using Microsoft.Xaml.Behaviors;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace LensSimulator.View._2DPlot
{
    /// <summary>
    /// Логика взаимодействия для Plot2D.xaml
    /// </summary>
    public partial class Plot2D : UserControl, IPlotObject, INotifyPropertyChanged
    {
        public Plot2D()
        {
            InitializeComponent();
        }
        private bool PlotObjectCanMove = false;
        private Point MouseOldCoord { get; set; }
        public double AxisWidth = 50.0;
        private RelayCommand? plot2DMouseDownCommand;
        public ICommand Plot2DMouseDownCommand => plot2DMouseDownCommand ??= new RelayCommand(Plot2DMouseDown);
        private void Plot2DMouseDown(object commandParameter)
        {
            PlotObjectCanMove = true;
            if (commandParameter is MouseButtonEventArgs e && e.Source is IInputElement target)
            {
                this.Cursor = Cursors.SizeAll;
                e.MouseDevice.Capture(target);
            }
        }

        private RelayCommand? plot2DMouseUpCommand;
        public ICommand Plot2DMouseUpCommand => plot2DMouseUpCommand ??= new RelayCommand(Plot2DMouseUp);
        private void Plot2DMouseUp(object commandParameter)
        {
            PlotObjectCanMove = false;
            if (commandParameter is MouseButtonEventArgs e)
            {
                this.Cursor = null;
                e.MouseDevice.Capture(null);
            }
        }
        public bool Move(UIElement target, double x, double y)
        {
            if(target != null)
            {
                Vector offset = VisualTreeHelper.GetOffset(target);
                Vector newOffset = new(offset.X + x, offset.Y + y);
                if (newOffset.X >= 0.0 && newOffset.Y >= 0.0 && newOffset.X<this.ActualWidth && newOffset.Y<this.ActualHeight)
                {
                    Canvas.SetLeft(target, offset.X + x);
                    Canvas.SetTop(target, offset.Y + y);
                    return true;
                }
                else
                {
                    this.Cursor = null;
                    PlotObjectCanMove = false;
                    return false;
                }
            }
            else
            {
                
                return false;
            }
            


        }

        private RelayCommand plot2DMouseMoveCommand;

        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));
        }

        public ICommand Plot2DMouseMoveCommand => plot2DMouseMoveCommand ??= new RelayCommand(Plot2DMouseMove);
        private void Plot2DMouseMove(object commandParameter)
        {
            if (commandParameter is MouseEventArgs e)
            {
                if (PlotObjectCanMove)
                {
                    if(e.Source is UIElement target)
                    {
                        Point CurrentMousePoint = e.GetPosition(this);
                        if (Move(target, CurrentMousePoint.X - MouseOldCoord.X, CurrentMousePoint.Y - MouseOldCoord.Y))
                        {
                            MouseOldCoord = CurrentMousePoint;
                        }
                        else {
                            e.MouseDevice.Capture(null);
                        };
                        
                    }
                }
                else
                {
                    MouseOldCoord = e.GetPosition(this);
                }
            }
        }        
    }
}
