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
    public partial class Plot2D : UserControl, INotifyPropertyChanged, IObjectMover
    {
        public Plot2D()
        {
            InitializeComponent();
            this.Loaded += Plot2D_Loaded;
        }
        private static void CreateGrid(Canvas target, double step, double u, double v, SolidColorBrush color, double thickness)
        {
            Point Offset = new((target.Parent as Grid).ActualWidth * 0.5, (target.Parent as Grid).ActualHeight * 0.5);
            for (int i = 1; i < u; ++i)
            {
                Line positiveXLine = new()
                {
                    X1 = i * step + Offset.X,
                    X2 = i * step + Offset.X,
                    Y1 = v * step + Offset.Y,
                    Y2 = -v * step + Offset.Y,
                    Fill = color,
                    Stroke = color,
                    StrokeThickness = thickness
                };
                Line negativeXLine = new()
                {
                    X1 = -i * step + Offset.X,
                    X2 = -i * step + Offset.X,
                    Y1 = v * step + Offset.Y,
                    Y2 = -v * step + Offset.Y,
                    Fill = color,
                    Stroke = color,
                    StrokeThickness = thickness
                };
                target.Children.Add(positiveXLine);
                target.Children.Add(negativeXLine);
            }
            for (int i = 1; i<v; i++)
            {
                Line positiveYLine = new()
                {
                    X1 = u * step + Offset.X,
                    X2 = -u * step + Offset.X,
                    Y1 = i * step + Offset.Y,
                    Y2 = i * step + Offset.Y,
                    Fill = color,
                    Stroke = color,
                    StrokeThickness = thickness
                };
                Line negativeYLine = new()
                {
                    X1 = u * step + Offset.X,
                    X2 = -u * step + Offset.X,
                    Y1 = -i * step + Offset.Y,
                    Y2 = -i * step + Offset.Y,
                    Fill = color,
                    Stroke = color,
                    StrokeThickness = thickness
                };
                target.Children.Add(positiveYLine);
                target.Children.Add(negativeYLine);
            }
            Line ZeroXLine = new()
            {
                X1 = Offset.X,
                X2 = Offset.X,
                Y1 = v * step + Offset.Y,
                Y2 = -v * step + Offset.Y,
                Fill = new SolidColorBrush(Color.FromRgb(128, 64, 0)),
                Stroke = new SolidColorBrush(Color.FromRgb(128, 64, 0)),
                StrokeThickness = thickness
            };
            Line ZeroYLine = new()
            {
                X1 = u * step + Offset.X,
                X2 = -u * step + Offset.X,
                Y1 = Offset.Y,
                Y2 = Offset.Y,
                Fill = new SolidColorBrush(Color.FromRgb(128, 64, 0)),
                Stroke = new SolidColorBrush(Color.FromRgb(128, 64, 0)),
                StrokeThickness = thickness
            };
            target.Children.Add(ZeroXLine);
            target.Children.Add(ZeroYLine);
        }
        private void Plot2D_Loaded(object sender, RoutedEventArgs e)
        {
            Size HalfSize = new Size(ActualWidth * 0.5, ActualHeight * 0.5);
            PlotOrigin = (Point)HalfSize;
            CreateGrid(BackgroundCanvas, 50, 200, 200, new SolidColorBrush(Color.FromRgb(64,32, 0)), 1);

        }

        private bool CoordinateSystemCanMove = false;
        private double PlotScaleFactor = 1.0;
        private double OffsetScaleFactor = 1.0;
        private double PlotZoomSpeed = 1.05;
        private Point PlotOrigin = new Point(0, 0); 
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

        public LensView? CurrentPickedObject
        {
            get { return (LensView)GetValue(CurrentPickedObjectProperty); }
            set { SetValue(CurrentPickedObjectProperty, value); }
        }
        public static readonly DependencyProperty CurrentPickedObjectProperty = DependencyProperty.Register(
            nameof(CurrentPickedObject), 
            typeof(LensView),
            typeof(Plot2D), 
            new PropertyMetadata(null, CurrentPickedObjectChangedCallback));

        private static void CurrentPickedObjectChangedCallback(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            if(e.NewValue != null && d is Plot2D && d != null)
            {
                (e.NewValue as LensView).SizeChanged += (d as Plot2D).CurrentPickedObjectSizeChanged;
            }
            if(e.OldValue != null && d is Plot2D && d != null)
            {
                (e.OldValue as LensView).SizeChanged -= (d as Plot2D).CurrentPickedObjectSizeChanged;
            }
        }

        private void CurrentPickedObjectSizeChanged(object sender, SizeChangedEventArgs e)
        {
            if (sender != null && e != null)
            {
                if (e.OriginalSource is LensView target)
                {
                    this.Move((target), -0.5 * PlotScaleFactor * (e.NewSize.Width - e.PreviousSize.Width), -0.5 * PlotScaleFactor * (e.NewSize.Height - e.PreviousSize.Height));
                }
            }
        }

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
                if(target != null)
                {
                    if (e.OriginalSource is Path)
                    {
                        if(((e.OriginalSource as Path).Parent as Grid).Parent is LensView targetLens)
                        {
                            CurrentPickedObject = targetLens;
                            MouseOldCoord = e.GetPosition(this);
                            CurrentPickedObjectPosition = MouseOldCoord;
                            this.Cursor = Cursors.SizeAll;
                            e.MouseDevice.Capture(targetLens);
                        }
                        
                    }
                    else if (target is Canvas)
                    {
                        CurrentPickedObject = null;
                        CoordinateSystemCanMove = true;
                    }
                }
            }
        }

        private RelayCommand? plot2DMouseUpCommand;
        public ICommand Plot2DMouseUpCommand => plot2DMouseUpCommand ??= new RelayCommand(Plot2DMouseUp);
        private void Plot2DMouseUp(object commandParameter)
        {
            PlotObjectCanMove = false;
            CoordinateSystemCanMove = false;
            CurrentPickedObjectPosition = new Point(0.0, 0.0);
            if (commandParameter is MouseButtonEventArgs e)
            {
                this.Cursor = null;
                e.MouseDevice.Capture(null);
            }
        }
        public bool Move(UIElement? target, double x, double y)
        {
            if (target != null)
            {
                Vector offset = VisualTreeHelper.GetOffset(target);
                Vector newOffset = new(offset.X + x, offset.Y + y);
                Canvas.SetLeft(target, newOffset.X);
                Canvas.SetTop(target, newOffset.Y);
                return true;
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
                Point offset = e.GetPosition(this);
                if (e.MouseDevice.Captured is IMoveableObject target && PlotObjectCanMove)
                {

                    if (target is ILensViewObject)
                    {
                        Move((UIElement)target, offset.X - MouseOldCoord.X, offset.Y - MouseOldCoord.Y);
                    }
                }else if (CoordinateSystemCanMove)
                {
                    foreach (var lens in Lenses) 
                    {
                        Move(lens, offset.X - MouseOldCoord.X, offset.Y - MouseOldCoord.Y);
                    }
                    foreach (Line PlotAxis in BackgroundCanvas.Children)
                    {
                        Move(PlotAxis, offset.X - MouseOldCoord.X, offset.Y - MouseOldCoord.Y);
                    }
                }
                MouseOldCoord = e.GetPosition(this);
                
            }
        }
        private RelayCommand plot2DMouseWheelCommand;

        public ICommand Plot2DMouseWheelCommand => plot2DMouseWheelCommand ??= new RelayCommand(Plot2DMouseWheel);
        private void Plot2DMouseWheel(object commandParameter)
        {
            if(Lenses != null)
            {
                
                if (commandParameter is MouseWheelEventArgs wheelParam)
                {
                    OffsetScaleFactor = wheelParam.Delta > 0 ? PlotZoomSpeed : 1 / PlotZoomSpeed;
                    PlotScaleFactor *= OffsetScaleFactor;
                    foreach (var lens in Lenses)
                    {
                        Point oldOffset = new(Canvas.GetLeft(lens), Canvas.GetTop(lens));
                        Point newOffset = new(oldOffset.X * OffsetScaleFactor, oldOffset.Y * OffsetScaleFactor);
                        Canvas.SetLeft(lens, newOffset.X);
                        Canvas.SetTop(lens, newOffset.Y);
                        var newTransform = new ScaleTransform(PlotScaleFactor, PlotScaleFactor, lens.ActualWidth * 0.5, lens.ActualHeight * 0.5);
                        lens.LayoutTransform = newTransform;
                    }
                    foreach (Line PlotAxis in BackgroundCanvas.Children)
                    {
                        Point newOffset = new(Canvas.GetLeft(PlotAxis) * OffsetScaleFactor, Canvas.GetTop(PlotAxis) * OffsetScaleFactor);
                        Canvas.SetLeft(PlotAxis, newOffset.X);
                        Canvas.SetTop(PlotAxis, newOffset.Y);
                        var newTransform = new ScaleTransform(PlotScaleFactor, PlotScaleFactor, PlotAxis.ActualWidth * 0.5, PlotAxis.ActualHeight * 0.5);
                        PlotAxis.LayoutTransform = newTransform;
                    }
                }
                
            }
        }
    }
}
