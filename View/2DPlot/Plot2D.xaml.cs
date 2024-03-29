﻿using LensSimulator.Commands;
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
            CreateGrid(BackgroundCanvas, 50, 200, 200, new SolidColorBrush(Color.FromRgb(64,32, 0)), 1);
            PlotOrigin = new(ActualWidth*0.5, ActualHeight*0.5);
        }

        private bool CoordinateSystemCanMove = false;
        private double AbsolutePlotScaleFactor = 1.0;
        private double RelativePlotScaleFactor = 1.0;
        private double PlotZoomSpeed = 1.05;
        private Point PlotOrigin = new Point(0, 0);
        private void Lenses_CollectionChanged(object? sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            if (e.NewItems != null && e.NewItems.Count > 0)
            {
                foreach (LensView? lens in e.NewItems)
                {
                    if (lens != null)
                    {
                        lens.Loaded += Lens_Loaded;
                    }
                }
            }
            OnPropertyChanged(nameof(Lenses));
        }

        private void Lens_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            Size oldSize = e.PreviousSize;
            Size newSize = e.NewSize;
            LensView? lens = sender as LensView;
            if (oldSize != newSize && lens != null)
            {
                Point sizeDelta = new Point(newSize.Width-oldSize.Width, newSize.Height-oldSize.Height);
                Point oldCoord = new Point(Canvas.GetLeft(lens), Canvas.GetTop(lens));
                Point newCoord = new Point(oldCoord.X-sizeDelta.X*0.5, oldCoord.Y-sizeDelta.Y*0.5);
                Canvas.SetLeft(lens, newCoord.X);
                Canvas.SetTop(lens, newCoord.Y);
            }
        }

        private void Lens_Loaded(object sender, RoutedEventArgs e)
        {
            LensView? lens = sender as LensView;
            if (lens != null)
            {
                Canvas.SetLeft(lens,-lens.ActualWidth * .5f + PlotOrigin.X);
                Canvas.SetTop(lens, -lens.ActualHeight * .5f + PlotOrigin.Y);
                lens.SizeChanged += Lens_SizeChanged;
                lens.PropertyChanged += Lens_PropertyChanged;
            }
        }


        private Point? currentLensCord = null;
        private void Lens_PropertyChanged(object? sender, PropertyChangedEventArgs e)
        {
            if (sender is LensView lens)
            {
                Point newCoordLens = new Point(lens.X, lens.Y);
                if (currentLensCord == null)
                {
                    currentLensCord = newCoordLens;
                }
                if (currentLensCord != newCoordLens && currentLensCord != null)
                {
                    Point oldOffset = new Point(lens.X - currentLensCord.Value.X, lens.Y - currentLensCord.Value.Y);
                    Point newOffset = new Point(Canvas.GetLeft(lens), Canvas.GetTop(lens));
                    Point delta = new Point(newOffset.X + oldOffset.X, newOffset.Y + oldOffset.Y);
                    Canvas.SetLeft(lens, delta.X);
                    Canvas.SetTop(lens, delta.Y);
                    currentLensCord = newCoordLens;
                }
            }

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
            new PropertyMetadata(null, CurrentPickedObjectChanged));

        private static void CurrentPickedObjectChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            if (d is Plot2D plot)
            {
                plot.currentLensCord = null;
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
                            MouseOldCoord = new (e.GetPosition(this).X / AbsolutePlotScaleFactor, e.GetPosition(this).Y / AbsolutePlotScaleFactor);
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
        private void MoveLens(LensView? lens, double x, double y)
        {
            if (lens != null)
            {
                lens.X += x;
                lens.Y += y;
            }
        }
        private RelayCommand plot2DMouseMoveCommand;
        public ICommand Plot2DMouseMoveCommand => plot2DMouseMoveCommand ??= new RelayCommand(Plot2DMouseMove);
        private void Plot2DMouseMove(object commandParameter)
        {
            if (commandParameter is MouseEventArgs e)
            {
                CurrentPickedObjectPosition = e.GetPosition(this);
                Point offset = new(e.GetPosition(this).X / AbsolutePlotScaleFactor, e.GetPosition(this).Y / AbsolutePlotScaleFactor); 
                var mouseOffset = new Point(offset.X - MouseOldCoord.X, offset.Y - MouseOldCoord.Y);
                if (e.MouseDevice.Captured is IMoveableObject target && PlotObjectCanMove)
                {
                    if (target is ILensViewObject)
                    {
                        var lensObject = (UserControl)target;

                        MoveLens(lensObject as LensView, mouseOffset.X, mouseOffset.Y);

                    }
                }else if (CoordinateSystemCanMove)
                {
                    foreach (var lens in Lenses) 
                    {
                        Move(lens, mouseOffset.X, mouseOffset.Y);
                    }
                    foreach (Line PlotAxis in BackgroundCanvas.Children)
                    {
                        Move(PlotAxis, mouseOffset.X, mouseOffset.Y);
                    }
                    PlotOrigin.X += mouseOffset.X;
                    PlotOrigin.Y += mouseOffset.Y;
                }
                MouseOldCoord = offset;

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
                    RelativePlotScaleFactor = wheelParam.Delta > 0 ? PlotZoomSpeed : 1 / PlotZoomSpeed;
                    AbsolutePlotScaleFactor *= RelativePlotScaleFactor;
                    var frontCanvasTransform = new ScaleTransform(AbsolutePlotScaleFactor, AbsolutePlotScaleFactor, ActualWidth*0.5, ActualHeight*0.5);
                    var backgroundCanvasTransform = new ScaleTransform(AbsolutePlotScaleFactor, AbsolutePlotScaleFactor, ActualWidth * 0.5, ActualHeight * 0.5);
                    FrontCanvas.LayoutTransform = frontCanvasTransform;
                    BackgroundCanvas.LayoutTransform = backgroundCanvasTransform;
                }
            }
        }
    }
}
