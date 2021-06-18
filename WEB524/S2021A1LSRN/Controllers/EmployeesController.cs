using S2021A1LSRN.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace S2021A1LSRN.Controllers
{
    public class EmployeesController : Controller
    {
        //Reference to Manager Controller
        private Manager mc = new Manager();

        // GET: Employees
        public ActionResult Index()
        {
            //Fetch collection from Manager object and pass collection to view
            return View(mc.EmployeeGetAll());
        }

        //GET: Employee
        public ActionResult Details(int? id)
        {
            var employee = mc.EmployeeGetOne(id.GetValueOrDefault());
            //var employee = mc.EmployeeGetOne(1);

            if (employee == null)
            {
                return HttpNotFound("page not found");
            }
            else
            {
                return View(employee);
            }
        }

        //Add New,HTTP Get Method
        public ActionResult Create()
        {
            //Create new object
            var emp = new EmployeeAddViewModel();

            return View(emp);
        }

        //HTTP Post
        [HttpPost]
        public ActionResult Create(EmployeeAddViewModel newEmployee)
        {
            //Validate incoming data
            if(!ModelState.IsValid)
            {
                return View(newEmployee);
            }

            try
            {
                var addEmp = mc.EmployeeAddNew(newEmployee);
                if (addEmp == null)
                {
                    return View(newEmployee);
                }
                else
                {
                    //Returns view 
                    return RedirectToAction("Details", new { id = addEmp.EmployeeId });
                }
            }
            catch
            {
                return View(newEmployee);
            }
        }

        public ActionResult Edit(int? id)
        {
            var employee = mc.EmployeeGetOne(id.GetValueOrDefault());


            if(employee == null)
            {
                return HttpNotFound("page not found");
            }
            else
            {
                return View(mc.mapper.Map<EmployeeBaseViewModel, EmployeeEditFormViewModel>(employee));
            }
        }

        [HttpPost]
        public ActionResult Edit(int? id, EmployeeEditViewModel model)
        {
            if (!ModelState.IsValid)
            {
                return RedirectToAction("Edit", new { id = model.EmployeeId });
            }

            if (id.GetValueOrDefault() != model.EmployeeId)
            {
                return View("Index");
            }

            var editedItem = mc.EmployeeEditExisting(model);

            if (editedItem == null)
            {
                return RedirectToAction("Edit", new { id = model.EmployeeId });
            }
            else
            {
                return RedirectToAction("Details", new { id = model.EmployeeId });
            }
        }
    }
}