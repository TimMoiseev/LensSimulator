using LensSimulator.Model.Lens;
using LensSimulator.View._2DPlot;
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

namespace LensSimulator.View.OpticElement
{
    /// <summary>
    /// Логика взаимодействия для LensView.xaml
    /// </summary>
    public partial class LensView : UserControl, INotifyPropertyChanged, ILensViewObject
    {
        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));
        }
        public static readonly DependencyProperty IdProperty =
            DependencyProperty.Register(
                nameof(Id),
                typeof(int?),
                typeof(LensView),
                new FrameworkPropertyMetadata(
                    null,
                    FrameworkPropertyMetadataOptions.AffectsMeasure | FrameworkPropertyMetadataOptions.AffectsRender,
                    OnLensViewPropertyChanged));

        private static void OnLensViewPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            (d as LensView).OnPropertyChanged(nameof(RStartPoint));
            (d as LensView).OnPropertyChanged(nameof(RPoint));
            (d as LensView).OnPropertyChanged(nameof(LStartPoint));
            (d as LensView).OnPropertyChanged(nameof(LPoint));
            (d as LensView).OnPropertyChanged(nameof(RSize));
            (d as LensView).OnPropertyChanged(nameof(LSize));
        }

        public int? Id
        {
            get => (int?)GetValue(IdProperty);
            set { SetValue(IdProperty, value); }
        }
        public static readonly DependencyProperty LensTypeProperty =
            DependencyProperty.Register(
                nameof(LensType), 
                typeof(LensModel.LensTypes), 
                typeof(LensView), 
                new FrameworkPropertyMetadata(
                    LensModel.LensTypes.DoubleConcaveLens, 
                    FrameworkPropertyMetadataOptions.AffectsMeasure | FrameworkPropertyMetadataOptions.AffectsRender, 
                    new PropertyChangedCallback(OnLensTypeChanged)));
        private static void OnLensTypeChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
        }

        public LensModel.LensTypes LensType
        {
            get { return (LensModel.LensTypes)GetValue(LensTypeProperty); }
            set { SetValue(LensTypeProperty, value); }
        }
        public static readonly DependencyProperty R1Property =
            DependencyProperty.Register(
                nameof(R1),
                typeof(double),
                typeof(LensView),
                new FrameworkPropertyMetadata(
                    0.0,
                    FrameworkPropertyMetadataOptions.AffectsMeasure| FrameworkPropertyMetadataOptions.AffectsRender,
                    OnLensViewPropertyChanged));
        public double R1
        {
            get => (double)GetValue(R1Property);
            set { SetValue(R1Property, value); }
        }
        public static readonly DependencyProperty R2Property =
            DependencyProperty.Register(
                nameof(R2),
                typeof(double),
                typeof(LensView),
                new FrameworkPropertyMetadata(
                    0.0,
                    FrameworkPropertyMetadataOptions.AffectsMeasure | FrameworkPropertyMetadataOptions.AffectsRender,
                    OnLensViewPropertyChanged));
        public double R2
        {
            get => (double)GetValue(R2Property);
            set { SetValue(R2Property, value); }
        }
        public static readonly DependencyProperty DProperty =
            DependencyProperty.Register(
                nameof(D),
                typeof(double),
                typeof(LensView),
                new FrameworkPropertyMetadata(
                    0.0,
                    FrameworkPropertyMetadataOptions.AffectsMeasure | FrameworkPropertyMetadataOptions.AffectsRender,
                    OnLensViewPropertyChanged));
        public double D
        {
            get => (double)GetValue(DProperty);
            set { SetValue(DProperty, value); }
        }
        public static readonly DependencyProperty HProperty =
            DependencyProperty.Register(
                nameof(H),
                typeof(double),
                typeof(LensView),
                new FrameworkPropertyMetadata(
                    0.0,
                    FrameworkPropertyMetadataOptions.AffectsMeasure | FrameworkPropertyMetadataOptions.AffectsRender,
                    OnLensViewPropertyChanged));
        public double H
        {
            get => (double)GetValue(HProperty);
            set { SetValue(HProperty, value); }
        }
        public static readonly DependencyProperty XProperty =
            DependencyProperty.Register(
                nameof(X),
                typeof(double),
                typeof(LensView),
                new FrameworkPropertyMetadata(
                    0.0,
                    FrameworkPropertyMetadataOptions.AffectsMeasure | FrameworkPropertyMetadataOptions.AffectsRender,
                    OnLensViewPropertyChanged));
        public double X
        {
            get => (double)GetValue(XProperty);
            set { SetValue(XProperty, value); }
        }
        public static readonly DependencyProperty YProperty =
            DependencyProperty.Register(
                nameof(Y),
                typeof(double),
                typeof(LensView),
                new FrameworkPropertyMetadata(
                    0.0,
                    FrameworkPropertyMetadataOptions.AffectsMeasure | FrameworkPropertyMetadataOptions.AffectsRender,
                    OnLensViewPropertyChanged));
        public double Y
        {
            get => (double)GetValue(YProperty);
            set { SetValue(YProperty, value); }
        }
        public static readonly DependencyProperty ZProperty =
            DependencyProperty.Register(
                nameof(Z),
                typeof(double),
                typeof(LensView),
                new FrameworkPropertyMetadata(
                    0.0,
                    FrameworkPropertyMetadataOptions.AffectsMeasure | FrameworkPropertyMetadataOptions.AffectsRender,
                    OnLensViewPropertyChanged));
        public double Z
        {
            get => (double)GetValue(ZProperty);
            set { SetValue(ZProperty, value); }
        }
        public Point RStartPoint { get { return new Point(H + R1 - Math.Sqrt(Math.Pow(R1, 2.0) - Math.Pow(D, 2.0) / 4.0), 0.0); } }
        public Point RPoint { get { return new Point(H + R1 - Math.Sqrt(Math.Pow(R1, 2.0) - Math.Pow(D, 2.0) / 4.0), D); } }
        public Size RSize { get { return new Size(R2, R2); } }
        public Point LStartPoint { get { return new Point(R1 - Math.Sqrt(Math.Pow(R1, 2.0) - Math.Pow(D, 2.0) / 4.0), 0.0); } }
        public Point LPoint { get { return new Point(R1 - Math.Sqrt(Math.Pow(R1, 2.0) - Math.Pow(D, 2.0) / 4.0), D); } }
        public Size LSize { get { return new Size(R1, R1); } }
        public SweepDirection RDirection { get { return SweepDirection.Clockwise; } }
        public SweepDirection LDirection { get { return SweepDirection.Counterclockwise; } }
        public LensView()
        {
            InitializeComponent();
        }
    }
}
