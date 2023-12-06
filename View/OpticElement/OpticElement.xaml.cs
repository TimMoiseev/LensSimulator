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

namespace LensSimulator.View.OpticElement
{
    /// <summary>
    /// Логика взаимодействия для OpticElement.xaml
    /// </summary>
    public partial class OpticElement : UserControl
    {
        public OpticElement(OpticElement oe)
        {
            InitializeComponent();
            this.circleUI.Width = oe.circleUI.Width;
            this.circleUI.Height = oe.circleUI.Height;
            this.circleUI.Fill = oe.circleUI.Fill;
        }
        protected override void OnMouseMove(MouseEventArgs e)
        {
            base.OnMouseMove(e);
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                DataObject dataObject = new DataObject();
                dataObject.SetData(DataFormats.StringFormat, circleUI.Fill.ToString());
                dataObject.SetData("Double", circleUI.Width);
                dataObject.SetData("Double", circleUI.Height);
                dataObject.SetData("Object", this);
                DragDrop.DoDragDrop(this, dataObject, DragDropEffects.Copy | DragDropEffects.Move);
            }
            
        }
        public OpticElement()
        {
            InitializeComponent();
        }
    }
}
