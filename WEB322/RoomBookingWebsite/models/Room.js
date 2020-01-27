const mongoose = require('mongoose');

const RoomSchema = new mongoose.Schema({
    title: 
    {
        type: String
    },
    price:
    {
        type: Number
    },
    description:
     {
        type: String
    },
    location:
    {
        type:String
    },
    roomImage:
    {
        type:String
    }
});

const model = mongoose.model('Room', RoomSchema);

module.exports = model;
