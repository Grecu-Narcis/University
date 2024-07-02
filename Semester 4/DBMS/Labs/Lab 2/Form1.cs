using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Configuration;

using System.Data.SqlClient;

namespace Lab_1
{
    public partial class Form1 : Form
    {
        SqlConnection conn;
        SqlDataAdapter parentDataAdapter;
        SqlDataAdapter childDataAdapter;
        DataSet dset;
        BindingSource parentBindingSource;
        BindingSource childBindingSource;

        SqlCommandBuilder cmdBuilder;

        string queryParent, queryChild;
        string parentTable, childTable, keyColumn;

        public Form1()
        {
            InitializeComponent();

            FillData();
        }

        void FillData()
        {
            conn = new SqlConnection(getConnectionString());

            parentTable = ConfigurationManager.AppSettings["parent"];
            childTable = ConfigurationManager.AppSettings["child"];
            keyColumn = ConfigurationManager.AppSettings["keyColumn"];

            parentLabel.Text = parentTable + ":";
            childLabel.Text = childTable + ":";

            queryParent = "SELECT * FROM " + parentTable;
            queryChild = "SELECT * FROM " + childTable;

            parentDataAdapter = new SqlDataAdapter(queryParent, conn);
            childDataAdapter = new SqlDataAdapter(queryChild, conn);

            dset = new DataSet();

            parentDataAdapter.Fill(dset, parentTable);
            childDataAdapter.Fill(dset, childTable);

            cmdBuilder = new SqlCommandBuilder(childDataAdapter);

            dset.Relations.Add("ParentChild",
                dset.Tables[parentTable].Columns[keyColumn],
                dset.Tables[childTable].Columns[keyColumn]);

            this.ParentDataGrid.DataSource = dset.Tables[parentTable];
            this.ChildDataGrid.DataSource = this.ParentDataGrid.DataSource;
            this.ChildDataGrid.DataMember = "ParentChild";

            cmdBuilder.GetUpdateCommand();
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void ParentDataGrid_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                childDataAdapter.Update(dset, childTable);
            }   
            
            catch (Exception ex)
            {
                MessageBox.Show("Database operation failed!\n" + ex.Message,
                    "Error",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        public string getConnectionString()
        {
            return "Data Source=NARCIS\\SQLEXPRESS02;" +
                "Initial Catalog=Github;Integrated Security=true;";
        }
    }
}
