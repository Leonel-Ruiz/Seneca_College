const mongoose = require('mongoose');
const Schema = mongoose.Schema;
const bcrypt = require('bcryptjs');


const reguistrationSchema = new Schema({
    emailI: 
    {
        type:String,
        required:true
    },
    firstNI: 
    {
        type:String,
        required:true
    },
    lastNI: 
    {
        type:String,
        required:true
    },
    passI: 
    {
        type:String,
        required:true
    },
    phoneI: 
    {
        type:Number,
        required:true
    },
    month: 
    {
        type:String,
        required:true
    },
    day: 
    {
        type:Number,
        required:true
    },
    year: 
    {
        type:Number,
        required:true
    },
    type:
    {
        type:String,
        default:"User"
    },
    dateCreated:
    {
        type:Date,
        default: Date.now()
    }
});

//The "pre" mongoose function is going to call the below function right before the document is saved to the DB
reguistrationSchema.pre("save",function(next){
  
    bcrypt.genSalt(10)
    .then(salt=>{
        bcrypt.hash(this.passI,salt)
        .then(hash=>{
            this.passI=hash
            // The below code is a call back function that does the following :
             //It forces the code of execution to  move onto the next code in the execution queue 
            next();
        })
    })

})

const userModel =mongoose.model("User",reguistrationSchema);
module.exports=userModel;