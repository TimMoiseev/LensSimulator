﻿using LensSimulator.View._2DPlot;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Security.Cryptography;
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
    /// Логика взаимодействия для OpticElementSettingsControl.xaml
    /// </summary>
    public partial class OpticElementSettingsControl : UserControl, INotifyPropertyChanged
    {
        public OpticElementSettingsControl()
        {
            InitializeComponent();
        }
        public static readonly DependencyProperty CurrentOpticElementProperty =
            DependencyProperty.Register(
                nameof(OpticElement), 
                typeof(LensView), 
                typeof(OpticElementSettingsControl), 
                new PropertyMetadata(null, CurrentOpticElementPropertyChanged));

        public LensView OpticElement
        {
            get { return (LensView)GetValue(CurrentOpticElementProperty); }
            set {  SetValue(CurrentOpticElementProperty, value);}
        }
        private static void CurrentOpticElementPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            if (e.NewValue is LensView newLens && d is OpticElementSettingsControl control)
            {
                control.D = newLens.D;
                control.R1 = newLens.R1;
                control.R2 = newLens.R2;
                control.H = newLens.H;
                control.X = newLens.X;
                control.Y = newLens.Y;
                control.Z = newLens.Z;
                control.OnPropertyChanged(nameof(D));
                control.OnPropertyChanged(nameof(R1));
                control.OnPropertyChanged(nameof(R2));
                control.OnPropertyChanged(nameof(H));
                control.OnPropertyChanged(nameof(X));
                control.OnPropertyChanged(nameof(Y));
                control.OnPropertyChanged(nameof(Z));
            }
        }
        private double _r1 = 0.0;
        private double _r2 = 0.0;
        private double _h = 0.0;
        private double _d = 0.0;
        private double _x = 0.0;
        private double _y = 0.0;
        private double _z = 0.0;

        public double R1
        {
            get { return _r1; }
            set { 
                _r1 = value;
                OnPropertyChanged(nameof(R1));
                OpticElement.R1 = value;
            }
        }
        public double R2
        {
            get { return _r2; }
            set { 
                _r2 = value;
                OnPropertyChanged(nameof(R2));
                OpticElement.R2 = value;
            }
        }
        public double D
        {
            get { return _d; }
            set { 
                _d = value; 
                OnPropertyChanged(nameof(D));
                OpticElement.D = value; 
            }
        }
        public double H
        {
            get { return _h; }
            set { 
                _h = value;
                OnPropertyChanged(nameof(H));
                OpticElement.H = value;
            }
        }
        public double X
        {
            get { return _x; }
            set { 
                _x = value;
                OnPropertyChanged(nameof(X));
                OpticElement.X = value;
            }
        }
        public double Y
        {
            get { return _y; }
            set { 
                _y = value;
                OnPropertyChanged(nameof(Y));
                OpticElement.Y = value;
            }
        }
        public double Z
        {
            get { return _z; }
            set { 
                _z = value;
                OnPropertyChanged(nameof(Z));
                OpticElement.Z = value;
            }
        }
        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));
        }
        

        
    }
}
