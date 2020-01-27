const express = require('express')
const router = express.Router();
const bcrypt= require("bcryptjs");


//This allows you to pefrom CRUD operations on the User colections 
const User = require("../models/User");

router.get("/", (req, res) => {

    //loads login.handlebars
    
    res.render("Login/login")
});



router.post("/", (req, res) => {
    /*************SERVER SIDE VALIDATION *******************/
    const errors_login = []; // array length is initially 0

    const formData = {
        email: req.body.emailI2,
        password: req.body.passI2,
        userType: req.body.type
    }

    //Validation for LOGIN FORM
    if (req.body.emailI2 == "") {
     errors_login.push("Please enter an Email")
    }

    if (req.body.passI2 == "") {
     errors_login.push("Please enter a password")
    }
    //User Model : form handlebars
    User.findOne({emailI:formData.email}) 
    .then(user=>{

        //This means that there was no matching email in the database
        if(user==null)
        {
            errors_login.push("Please enter a valid user") 
            res.render("Login/login",{
                message:errors_login
            })
        }
        else
        {
            bcrypt.compare(formData.password,user.passI)
            .then(isMatched=>{
                if(isMatched==true)
                {
                    //It means that the user is authenticated 

                    //Create session 
                    req.session.userInfo=user;
                    if(user.type == "User")
                    {
                        res.redirect("/DashboardUser");
                    }
                    else
                    {
                        res.redirect("/DashboardAdmin");
                    }
                }
                else
                {
                    errors_login.push("Incorrect Password");
                    res.render("Login/login",{
                        message:errors_login
                    })
                }
            })
            .catch(errors_login=>console.log(`Error occured ${errors_login}`));
        }
    })
    .catch(errors_login=> console.log(`Error occured ${errors_login}`));  
});


module.exports=router;