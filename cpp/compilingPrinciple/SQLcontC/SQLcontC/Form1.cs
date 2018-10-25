using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace SQLcontC
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string ConStr = "server =localhost;user id=sa;pwd=12;database = bank";
            SqlConnection conn = new SqlConnection(ConStr);
            string SqlStr = "select * from bank.customer";
            SqlDataAdapter ada = new SqlDataAdapter(SqlStr, conn);
            conn.Open();
            DataSet ds = new DataSet();
            ada.Fill(ds);
            dataGridView1.DataSource = ds.Tables[0];
            //GridView1.DataBind();
            conn.Close();
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
