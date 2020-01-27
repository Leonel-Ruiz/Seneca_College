const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const locationSchema = new Schema({
    name: String
});

const model = mongoose.model("location", locationSchema);

module.exports = model;