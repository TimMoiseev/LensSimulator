using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.DirectoryServices;
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
    /// Логика взаимодействия для AxisLine2D.xaml
    /// </summary>
    public partial class AxisLine2D : UserControl, IPlotObject, INotifyPropertyChanged
    {
        public AxisLine2D()
        {
            InitializeComponent();
        }


        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));
        }
        public bool Move(UIElement target, double x, double y) { return false; }
    }
}
