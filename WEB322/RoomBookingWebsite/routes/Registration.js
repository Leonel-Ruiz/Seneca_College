const express = require('express')
const router = express.Router();
const bcrypt= require("bcryptjs");


//This allows you to pefrom CRUD operations on the User colections 
const User = require("../models/User");

router.get("/", (req, res) => {

    //loads registration.handlebars
    res.render("Registration/registration")
});



//called when login form submitted
router.post("/", (req, res) => {
    
    const formData = {
        emailI: req.body.emailI,
        firstNI: req.body.firstNI,
        lastNI: req.body.lastNI,
        passI: req.body.passI,
        phoneI: req.body.phoneI,
        month: req.body.month,
        day: req.body.day,
        year: req.body.year
        
    }
    
    /*************SERVER SIDE VALIDATION *******************/
    const errors = []; // array length is initially 0

        if(!/^((?=.*[a-zA-Z])(?=.*[0-9])).{6,12}$/.test(req.body.passI)) 
        {    
            errors.push("Password must be 6-12 characters, contain at least one letter and one number")
        }
    
    // AGE VALIDATION
    
        var currentYear = new Date().getFullYear();
        var userYear = req.body.year;
        var userAge = currentYear-userYear;
          if(userAge < 19) 
        {    
            errors.push("You must be 19 years or older")
        }

    //Validation for REGISTRATION FORM
    if (req.body.emailI == "") 
    {
        errors.push("Please enter an Email")
    }

    if (req.body.firstNI == "") 
    {
        errors.push("Please enter First Name")
    }

    if (req.body.lastNI == "")
    {
        errors.push("Please enter Last Name")
    }

    if (req.body.passI == "") 
    {
        errors.push("Please enter a Password")
    }

    if (req.body.phoneI == "") 
    {
        errors.push("Please enter a Phone Number")
    }

    if ((req.body.passI.localeCompare(req.body.cpassword)) != 0 )
    {
        errors.push("The passwords do not match")
    }

    User.findOne({emailI:formData.emailI})
    .then(user=>{
        //This means that there was no matching email in the database
        if(user==null)
        {
            errors.push("The user already exist")
        }
    });
        
    
   
     //This means that there are errors therefore we want to re-render the current form
     if (errors.length > 0) 
     {
           res.render("Registration/registration",
           {
              message:errors 
           })
     }
     else 
     {
         // SEND SMS TEXT 
 
         const accountSid = process.env.ACCOUNT_S_ID;
         const authToken = process.env.AUTH_TOKEN;
         const client = require('twilio')(accountSid, authToken);
 
         client.messages
             .create({
                 body: `Congratulations! Your account has been registered successfully`,
                 from: '+12015716656',
                 to: `${req.body.phoneI}`
             })
             .then(message => console.log(message.sid))
             .catch(error => console.log(`${error}`));
 
         // SEND THE EMAIL
         const nodemailer = require('nodemailer');
         const sgTransport = require('nodemailer-sendgrid-transport');
 
         const options = {
             auth: {
                 api_key: process.env.API_KEY
             }
         }
 
         const mailer = nodemailer.createTransport(sgTransport(options));
 
         const email = {
             to: `${req.body.emailI}`,
             from: 'lruiz-navarrete@myseneca.ca',
             subject: 'Account Confirmation',
             text: `Congratulations! Your account has been registered successfully`,
             html: ``
         }
         mailer.sendMail(email, (err, res) => {
             if (err) {
                 console.log(err)
             }
             console.log(res);
         });

    //This creates a Model called Users. This model represents our Collection in our database
   // const User = mongoose.model('Users', reguistrationSchema);

   //To create a  Task document we have to call the Model constructor
   const user = new User(formData);

    user.save()
        .then(() => {
            console.log('Task was inserted into database')
        })
        .catch((err) => {
            console.log(`Task was not inserted into the database because ${err}`)
        })
         //REDIRECT THE USER 
         res.redirect("/DashboardUser");
     };
});

module.exports=router;