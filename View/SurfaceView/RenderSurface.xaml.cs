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
using static LensSimulator.Model.Graphics.EngineState;
namespace LensSimulator.View.SurfaceView
{
    /// <summary>
    /// Логика взаимодействия для RenderSurface.xaml
    /// </summary>
    public partial class RenderSurface : UserControl
    {
        private Win32SurfaceView surfaceView;
        public RenderSurface()
        {
            InitializeComponent();
            Loaded += RenderSurface_Loaded;
        }

        private void RenderSurface_Loaded(object sender, RoutedEventArgs e)
        {
            surfaceView = new Win32SurfaceView();
            
            Content = surfaceView;
        }
    }
}
