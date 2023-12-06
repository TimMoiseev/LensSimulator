using System;
using System.Collections.Generic;
using System.Linq;
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

namespace LensSimulator.View.OpticElementPicker
{
    /// <summary>
    /// Логика взаимодействия для OpticElementPicker.xaml
    /// </summary>
    public partial class OpticElementPicker : UserControl
    {
        public ImageSource? ImageSource { get; set; }
        public string? Text { get; set; }
        public OpticElementPicker()
        {
            InitializeComponent();
            DataContext = this;
        }
    }
}
