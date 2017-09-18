package psosm;

import java.awt.*;  
import java.awt.event.*;
import javax.swing.*;
public class ButtonExample {  
public static void main(String[] args) {  
    Frame f=new Frame("Button Example"); 
    JTextField t1;  
    t1=new JTextField("Welcome to Test Path Optimization tool");  
    t1.setBounds(50,50, 300,30);  
  
    f.add(t1);
    
   /* final TextField tf=new TextField();  
    tf.setBounds(50,50, 50,200); 
    final TextField tf2=new TextField();  
    tf2.setBounds(400,300, 150,20); */
    Button b=new Button("1.Genetic Algorithm");  
    b.setBounds(50,100,260,30); 
    Button b3=new Button("2.ACO Algorithm");  
    b3.setBounds(50,200,260,30); 
    Button b2=new Button("3.Hybrid Genetic Algorithm");  
    b2.setBounds(50,300,260,30); 
    /*b.addActionListener(new ActionListener(){  
    public void actionPerformed(ActionEvent e){  
            tf.setText("Welcome to Javatpoint.");  
        }  
     
    });
    b2.addActionListener(new ActionListener(){  
        public void actionPerformed(ActionEvent e){  
                tf2.setText("Welcome to Javatpoint.");  
            }  
         
        }); */
    f.add(b);//f.add(tf); 
    //f.add(tf2);
    f.add(b2);
    f.add(b3);
    f.setSize(400,400);  
    f.setLayout(null);  
    f.setVisible(true);   
}  
}  