using LensSimulator.Commands;
using LensSimulator.View.OpticElement;
using Microsoft.Xaml.Behaviors;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
    public partial class Plot2D : UserControl, INotifyPropertyChanged
    {
        public Plot2D()
        {
            
            InitializeComponent();
        }

        private void Lenses_CollectionChanged(object? sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            OnPropertyChanged();
        }

        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));
        }

        public static readonly DependencyProperty LensesProperty =
            DependencyProperty.Register(nameof(Lenses), typeof(ObservableCollection<LensView>), typeof(Plot2D), new PropertyMetadata(null, LensesPropertyChangedCallback));

        private static void LensesPropertyChangedCallback(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var oldCollection = e.OldValue as ObservableCollection<LensView>;
            var newCollection = e.NewValue as ObservableCollection<LensView>;
            if(oldCollection != null)
            {
                oldCollection.CollectionChanged -= (d as Plot2D).Lenses_CollectionChanged;
            }
            if(newCollection != null)
            {
                newCollection.CollectionChanged += (d as Plot2D).Lenses_CollectionChanged;
            }
            
        }

        public ObservableCollection<LensView> Lenses
        {
            get { return (ObservableCollection<LensView>)GetValue(LensesProperty); }
            set { SetValue(LensesProperty, value); }
        }

        private LensView? _currentPickedObject = null;
        public LensView? CurrentPickedObject
        {
            get { return (LensView)GetValue(CurrentPickedObjectProperty); }
            set { SetValue(CurrentPickedObjectProperty, value); }
        }
        public static readonly DependencyProperty CurrentPickedObjectProperty = DependencyProperty.Register(nameof(CurrentPickedObject), typeof(LensView), typeof(Plot2D), new PropertyMetadata());

        private bool PlotObjectCanMove = false;
        private Point MouseOldCoord { get; set; }
        public Point? CurrentPickedObjectPosition { get; private set; }

        private RelayCommand? plot2DMouseDownCommand;
        public ICommand Plot2DMouseDownCommand => plot2DMouseDownCommand ??= new RelayCommand(Plot2DMouseDown);
        private void Plot2DMouseDown(object commandParameter)
        {
            PlotObjectCanMove = true;
            if (commandParameter is MouseButtonEventArgs e && e.Source is IInputElement target)
            {
                if (target is LensView targetObject)
                {
                    CurrentPickedObject = targetObject;
                }
                MouseOldCoord = e.GetPosition(this);
                CurrentPickedObjectPosition = MouseOldCoord;
                this.Cursor = Cursors.SizeAll;
                e.MouseDevice.Capture(target);
            }
        }

        private RelayCommand? plot2DMouseUpCommand;
        public ICommand Plot2DMouseUpCommand => plot2DMouseUpCommand ??= new RelayCommand(Plot2DMouseUp);
        private void Plot2DMouseUp(object commandParameter)
        {
            PlotObjectCanMove = false;
            CurrentPickedObjectPosition = new Point(0.0, 0.0);
            if (commandParameter is MouseButtonEventArgs e)
            {
                this.Cursor = null;
                e.MouseDevice.Capture(null);
            }
        }
        public bool Move(IMoveableObject target, double x, double y)
        {
            if (target != null)
            {
                Vector offset = VisualTreeHelper.GetOffset((UIElement)target);
                Vector newOffset = new(offset.X + x, offset.Y + y);
                if (newOffset.X >= 0.0 && newOffset.Y >= 0.0 && newOffset.X < this.ActualWidth && newOffset.Y < this.ActualHeight)
                {
                    Canvas.SetLeft((UIElement)target, offset.X + x);
                    Canvas.SetTop((UIElement)target, offset.Y + y);
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
        public Point? ElementCoordinateToPlotCoordinate(IDrawableObject element)
        {
            if (element != null)
            {
                Point HalfElementSize = new Point(((UserControl)element).ActualWidth / 2.0, ((UserControl)element).ActualHeight / 2.0);
                Point ElementOffset = new Point(Canvas.GetLeft((UIElement)element), Canvas.GetTop((UIElement)element));
                return (Point)((Vector)ElementOffset + (Vector)HalfElementSize);
            }
            else { return null; }
        }
        private RelayCommand plot2DMouseMoveCommand;

        public ICommand Plot2DMouseMoveCommand => plot2DMouseMoveCommand ??= new RelayCommand(Plot2DMouseMove);
        private void Plot2DMouseMove(object commandParameter)
        {
            if (commandParameter is MouseEventArgs e)
            {
                CurrentPickedObjectPosition = e.GetPosition(this);
                if (e.Source is IMoveableObject target && PlotObjectCanMove)
                {
                    if (target is ILensViewObject)
                    {
                        Point CurrentMousePoint = e.GetPosition(this);
                        if (Move(target, CurrentMousePoint.X - MouseOldCoord.X, CurrentMousePoint.Y - MouseOldCoord.Y))
                        {
                            MouseOldCoord = CurrentMousePoint;
                            CurrentPickedObjectPosition = ElementCoordinateToPlotCoordinate((IDrawableObject)target);
                        }
                    }
                    else if (target is ISupportingGraphicsObject)
                    {

                    }

                }
            }
        }
    }
}
