// **************************************************
// WEB524 Project Template V1 == 67d8d727-b1a1-480a-a35f-697f9903b2ac
// Do not change this header.
// **************************************************

using AutoMapper;
using S2021A1LSRN.EntityModels;
using S2021A1LSRN.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace S2021A1LSRN.Controllers
{
    public class Manager
    {
        // Reference to the data context
        private DataContext ds = new DataContext();

        // AutoMapper instance
        public IMapper mapper;

        public Manager()
        {
            // If necessary, add more constructor code here...

            // Configure the AutoMapper components
            var config = new MapperConfiguration(cfg =>
            {
                // Define the mappings below, for example...
                cfg.CreateMap<Employee, EmployeeBaseViewModel>();

                cfg.CreateMap<EmployeeAddViewModel, Employee>();

                cfg.CreateMap<EmployeeBaseViewModel, EmployeeEditFormViewModel>();
                

            });

            mapper = config.CreateMapper();

            // Turn off the Entity Framework (EF) proxy creation features
            // We do NOT want the EF to track changes - we'll do that ourselves
            ds.Configuration.ProxyCreationEnabled = false;

            // Also, turn off lazy loading...
            // We want to retain control over fetching related objects
            ds.Configuration.LazyLoadingEnabled = false;
        }

        // Add your methods and call them from controllers.  Use the suggested naming convention.
        // Ensure that your methods accept and deliver ONLY view model objects and collections.
        // When working with collections, the return type is almost always IEnumerable<T>.
        // Suggested naming convention: Entity + task/action

        //Method 1: Get All: Returns a collection of base view model objects
        public IEnumerable<EmployeeBaseViewModel> EmployeeGetAll()
        {
            //gets and sorts employees from database
            var sortEmployees = ds.Employees
                                  .OrderBy(e => e.LastName)
                                  .ThenBy(e => e.FirstName);
            
            //Returning new mapped collection of sorted employees
            return mapper.Map<IEnumerable<Employee>, IEnumerable<EmployeeBaseViewModel>>(sortEmployees);
        }
        
        //Method 2: Get One
        public EmployeeBaseViewModel EmployeeGetOne(int emp_id)
        {
            //Tries to get employee
            var Emp = ds.Employees.Find(emp_id);

            //If not found returns null, otherwise returs mapped object
            return Emp == null ? null : mapper.Map<Employee, EmployeeBaseViewModel>(Emp);
        }

        //Method  3: Add New
        public EmployeeBaseViewModel EmployeeAddNew(EmployeeAddViewModel newEmployee)
        {
            //Try to add new employee to database
            var addEmployee = ds.Employees.Add(mapper.Map<EmployeeAddViewModel, Employee>(newEmployee));

            //Saves changes in database
            ds.SaveChanges();

            //If successful returns mapped object, otherwise null
            return addEmployee == null ? null : mapper.Map<Employee, EmployeeBaseViewModel>(addEmployee);
        }

        //Method 4: Edit Existig
        public EmployeeBaseViewModel EmployeeEditExisting(EmployeeEditViewModel employee)
        {
            //Try to find employee
            var emp = ds.Employees.Find(employee.EmployeeId);

            //If found 
            if(emp != null)
            {
                //Make changes
                ds.Entry(emp).CurrentValues.SetValues(employee);

                //Save changes into database
                ds.SaveChanges();

                //Return updated object 
                return mapper.Map<Employee, EmployeeBaseViewModel>(emp);
            }
            else
            {
                //if employee not found in database returns null
                return null;
            }
        }

    }
}