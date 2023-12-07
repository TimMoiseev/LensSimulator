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
        private bool hasFullSize = false;
        public bool HaveFullSize { get; set; }

        public enum OpticElementType
        {
            DoubleConvexLens = 0,
            PlanoConvexLens = 1,
            PositiveMeniscusLens = 2,
            NegativeMeniscusLens = 3,
            PlanoConcaveLens = 4,
            DoubleConcaveLens = 5
        }
        private Dictionary<OpticElementType, string> TypeToIconPath = new()
        {
            { OpticElementType.PlanoConvexLens, "pack://application:,,,/Resource/lens/PlanoConvexLens.png" },
            { OpticElementType.DoubleConvexLens, "pack://application:,,,/Resource/lens/BiConvexLens.png" },
            { OpticElementType.PositiveMeniscusLens, "pack://application:,,,/Resource/lens/PositiveMeniscusLens.png" },
            { OpticElementType.NegativeMeniscusLens, "pack://application:,,,/Resource/lens/NegativeMeniscusLens.png" },
            { OpticElementType.PlanoConcaveLens, "pack://application:,,,/Resource/lens/PlanoConcaveLens.png" },
            { OpticElementType.DoubleConcaveLens, "pack://application:,,,/Resource/lens/DoubleConcaveLens.png" }
        };
        private Dictionary<OpticElementType, string> TypeToImagePath = new()
        {
            { OpticElementType.PlanoConvexLens, "pack://application:,,,/Resource/lens/FullSizeImage/PlanoConvexLensFull.png" },
            { OpticElementType.DoubleConvexLens, "pack://application:,,,/Resource/lens/FullSizeImage/DoubleConvexLensFull.png" },
            { OpticElementType.PositiveMeniscusLens, "pack://application:,,,/Resource/lens/FullSizeImage/PositiveMeniscusLensFull.png" },
            { OpticElementType.NegativeMeniscusLens, "pack://application:,,,/Resource/lens/FullSizeImage/NegativeMeniscusLensFull.png" },
            { OpticElementType.PlanoConcaveLens, "pack://application:,,,/Resource/lens/FullSizeImage/PlanoConcaveLensFull.png" },
            { OpticElementType.DoubleConcaveLens, "pack://application:,,,/Resource/lens/FullSizeImage/DoubleConcaveLensFull.png" }
        };
        private OpticElementType type;
        public OpticElementType Type {
            get { return type; }
            set {
                type = value;
                LensIcon.Source = (ImageSource)new ImageSourceConverter().ConvertFromString(TypeToIconPath[type]);
            } }
        public OpticElement(bool FullSize, OpticElement oe)
        {
            InitializeComponent();
            this.Width = oe.Width;
            this.Height = oe.Height;
            this.LensIcon.Source = FullSize ? 
                (ImageSource)new ImageSourceConverter().ConvertFromString(TypeToImagePath[oe.type]) :
                (ImageSource)new ImageSourceConverter().ConvertFromString(TypeToIconPath[oe.type]);
        }
        protected override void OnMouseMove(MouseEventArgs e)
        {
            base.OnMouseMove(e);
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                DataObject dataObject = new DataObject();
                //dataObject.SetData(DataFormats.StringFormat, opticElementUI.Fill.ToString());
                //dataObject.SetData("Double", opticElementUI.Width);
                //dataObject.SetData("Double", opticElementUI.Height);
                dataObject.SetData("Enum", Type);
                dataObject.SetData("Object", this);
                DragDrop.DoDragDrop(this, dataObject, DragDropEffects.Copy | DragDropEffects.Move);
            }
            
        }
        public OpticElement()
        {
            InitializeComponent();
            DataContext = this;
        }
    }
}
