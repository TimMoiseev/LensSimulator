using System;
using System.Globalization;
using System.Windows;
using System.Windows.Data;

namespace LensSimulator.Converters
{
    public class HalfDoubleValueConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is double)
            {
                return (double)value / 2;
            }
            return value;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is double)
            {
                double doubleValue = (double)value;
                return doubleValue * 2;
            }

            return DependencyProperty.UnsetValue;
        }
    }
}
