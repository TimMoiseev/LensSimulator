
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

namespace LensSimulator.View.UpDownButton
{
    /// <summary>
    /// Логика взаимодействия для NumericUpDownButton.xaml
    /// </summary>
    public partial class NumericUpDownButton : UserControl
    {
        public NumericUpDownButton()
        {
            InitializeComponent();
        }
        public double Number
        {
            get { return (double)GetValue(NumberProperty); }
            set { SetValue(NumberProperty, value); }
        }
        public static readonly DependencyProperty NumberProperty = DependencyProperty.Register(nameof(Number), typeof(double), typeof(NumericUpDownButton), new PropertyMetadata(0.0, NumberPropertyChanged));

        private static void NumberPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
        }

        private void ButtonUp_Click(object sender, RoutedEventArgs e)
        {
            if (Keyboard.Modifiers == ModifierKeys.Control)
            {
                Number += 1.0;
            }
            else if (Keyboard.Modifiers == ModifierKeys.Alt) {
                Number += 10.0;
            }
            else
            {
                Double num = Math.Round(Number + .1, 3);
                Number = num;
            }
        }

        private void ButtonDown_Click(object sender, RoutedEventArgs e)
        {
            if (Keyboard.Modifiers == ModifierKeys.Control)
            {
                Number -= 1.0;
            }
            else if (Keyboard.Modifiers == ModifierKeys.Alt)
            {
                Number -= 10.0;
            }
            else
            {
                Number -= 0.1;
            }
        }
    }
}
