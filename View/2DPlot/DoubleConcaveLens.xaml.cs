using LensSimulator.Commands;
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
using System.Xml.Linq;

namespace LensSimulator.View._2DPlot
{
    /// <summary>
    /// Логика взаимодействия для DoubleConcaveLens.xaml
    /// </summary>
    public partial class DoubleConcaveLens : UserControl, INotifyPropertyChanged
    {
        public DoubleConcaveLens()
        {
            InitializeComponent();
        }
        
        private double _D = 120.0;
        private double _R = 180.0;
        private double _h = 10.0;
        private double _scale = 1.0;
        public double ScaleFactor { get { return _scale; } set { _scale = value; OnPropertyChanged(); } }
        public double D { get { return _D * _scale; } set { _D = value; OnPropertyChanged(); } }
        public double R { get { return _R * _scale; } set { _R = value; OnPropertyChanged(); } }
        public double H { get { return _h * _scale; } set { _h = value; OnPropertyChanged(); } }
        public Point RStartPoint { get { return new Point(H + R - Math.Sqrt(Math.Pow(R, 2.0) - Math.Pow(D, 2.0) / 4.0), 0.0); } }
        public Point RPoint { get { return new Point(H + R - Math.Sqrt(Math.Pow(R, 2.0) - Math.Pow(D, 2.0) / 4.0), D); } }
        public Size RSize { get { return new Size(R, R); } }
        public Point LStartPoint { get { return new Point(R - Math.Sqrt(Math.Pow(R, 2.0) - Math.Pow(D, 2.0)/4.0), 0.0); } }
        public Point LPoint { get { return new Point(R - Math.Sqrt(Math.Pow(R, 2.0) - Math.Pow(D, 2.0) / 4.0), D); } }
        public Size LSize { get { return new Size(R, R); } }


               
        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));
        }

        public bool Hide()
        {
            throw new NotImplementedException();
        }

        public bool Delete()
        {
            throw new NotImplementedException();
        }

        public bool Scale(double factor)
        {
            ScaleFactor = factor;
            return true;
        }
    }
}
