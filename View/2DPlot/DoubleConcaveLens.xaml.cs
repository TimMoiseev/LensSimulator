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
    /// Логика взаимодействия для DoubleConcaveLens.xaml
    /// </summary>
    public partial class DoubleConcaveLens : UserControl, IPlotObject, INotifyPropertyChanged
    {
        public DoubleConcaveLens()
        {
            InitializeComponent();
        }
        private double _Width = 100.0;
        private double _Height = 100.0;
        private double _D = 40;
        private double _R = 40;
        private double _h = 10;
        public double ElementWidth
        {
            get
            {
                return _Width;
            }
        }
        public double ElementHeight { get { return _Height; } }
        public double D { get { return _D; } set { _D = value; OnPropertyChanged(); } }
        public double R { get { return _R; } set { _R = value; OnPropertyChanged(); } }
        public double H { get { return _h; } set { _h = value; OnPropertyChanged(); } }
        public Point RStartPoint { get { return new Point(H / 2.0 + _Width / 2.0, -R + _Height / 2.0); } }
        public Point RPoint { get { return new Point(H / 2.0 + _Width / 2.0, R + _Height / 2.0); } }
        public Size RSize { get { return new Size(R * 2.0, R * 2.0); } }
        public Point LStartPoint { get { return new Point(-H / 2.0 + _Width / 2.0, -R + _Height / 2.0); } }
        public Point LPoint { get { return new Point(-H / 2.0 + _Width / 2.0, R + _Height / 2.0); } }
        public Size LSize { get { return new Size(R * 2.0, R * 2.0); } }

        public void SetParameters(double diameter, double R, double h)
        {
            _D = diameter;
            this._R = R;
            this._h = h;
            OnPropertyChanged();
        }

        public (double, double) Position => (ActualWidth, ActualHeight);

        public void Move(double x, double y)
        {
            Canvas.SetLeft(this, x);
            Canvas.SetTop(this, y);
        }
        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
        }
    }
}
