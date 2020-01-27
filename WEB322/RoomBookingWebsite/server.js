/*
    Web 322: Assignment 1
    Student: Leonel Said Ruiz Navarrete
    ID: 104657184
    Email: lruiz-navarrete@myseneca.ca
*/

//Imports express package to the js file.
const express = require("express");
const exphbs = require('express-handlebars');
const bodyParser = require('body-parser');
const mongoose = require('mongoose');
const fileupload=require('express-fileupload');
const session = require("express-session");
const methodOverride=require('method-override')


//This loads all our environment variables from the keys.env
require("dotenv").config({path:'./config/keys.env'});

//import your router objects
const dashboardRoutes = require("./routes/DashboardUser");
const roomRoutes = require("./routes/Room");
const generalRoutes = require("./routes/General");
const loginRoutes = require("./routes/LoginAuthentication");
const logoutRoutes = require("./routes/Logout");
const registrationRoutes = require("./routes/Registration");
const AdashboardRoutes = require("./routes/DashboardAdmin");
const AddRoomRoutes = require("./routes/AddRoom");

Routes = require("./routes/LoginAuthentication");

//Creates express object
const app = express();

// It tells Express to parse submitted data from forms into the body of object
app.use(bodyParser.urlencoded({ extended: false }))

app.use(fileupload())
app.use(methodOverride('_method'));

//const mongoose = require('mongoose');

//Loads statics assets(css, images, js) from the public folder.
app.use(express.static('public'));

app.use(session({secret:"This is my secret key. This should not be shown to everyone"}))

app.use(session({
    secret: process.env.SESSION_SECRET_KEY
  }));

app.use((req,res,next)=>{

    //This is a global variable that can be accessed by templates
    res.locals.user= req.session.userInfo;
    next();
})

//MAPs EXPRESS TO ALL OUR  ROUTER OBJECTS
app.use("/",generalRoutes);
app.use("/dashboardUser",dashboardRoutes);
app.use("/room",roomRoutes);
app.use("/login",loginRoutes);
app.use("/logout",logoutRoutes);
app.use("/registration",registrationRoutes);
app.use("/dashboardAdmin",AdashboardRoutes);
app.use("/logout",loginRoutes);
app.use("/addRoom",AddRoomRoutes);
//app.use("/authentication",authenticationRoutes);

//Tells express that I want to use handlebars as template engine
app.engine('handlebars', exphbs());
app.set('view engine', 'handlebars');



//Meant to connect mongoose to our MONGODB in the Cloud 
//const DBURL = "mongodb+srv://LEO_A3:Aplication8475G@cluster0-rwcqr.mongodb.net/test?retryWrites=true&w=majority";
const DBURL =`mongodb+srv://${process.env.MONGO_DB_USERNAME}:${process.env.MONGO_DB_PASSWORD}@cluster0-rwcqr.mongodb.net/${process.env.MONGO_DB_DATABASE_NAME}?retryWrites=true&w=majority`;
mongoose.connect(DBURL, { useNewUrlParser: true })
    //The then block will only be executed if the above-mentioned line is successful
    .then(() => {
        console.log(`Database is connected`)
    })
    //The catch block will only be executed if the connection failed
    .catch(err => {
        console.log(`Something went wrong : ${err}`);
    })


//Creates Express Web Server that will "sit" in my web application that listens to the 
//HTTP requests and responds to routes
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {

    console.log(`The Web Server started at PORT :${PORT}`);
});