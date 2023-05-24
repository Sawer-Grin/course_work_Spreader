const mongoose = require("sequelize");
const Schema = mongoose.Schema;

// Creating a schema for our database
// const fileSchema = new Schema(
//   {
//     file_id: {}
//     filename: { type: String, required: true },
//     path: { type: String, required: true },
//     size: { type: Number, required: true },
//     uuid: { type: String, required: true },
//     sender: { type: String, required: false },
//     receiver: { type: String, required: false },
//   },
//   { timestamps: true }
// );

// creating a model and exporting it
// with name = File and passing Schema = fileSchema
// module.exports = mongoose.model("File", fileSchema);

module.exports = (sequelize, Sequelize, table_name) => {
  const File = sequelize.define('user_info',{
    uuid: {
      type: Sequelize.UUID,
      allowNull: false,
      primaryKey: true,
      autoIncrement: true,
    },
    size: {
      type: Sequelize.BIGINT,
      allowNull: false,
    },
    sender: {
      type: Sequelize.STRING,
      allowNull: true,
    },
    receiver: {
      type: Sequelize.STRING,
      allowNull: true,
    },
    time_created: {
      type: Sequelize.DATE,
    },
    last_moment: {
      type: Sequelize.DATE,
      allowNull: false,
    },
    status: {
      type: Sequelize.ENUM(
        "Uploaded", "Unclenched", "ReadyToSend", "Deleted"),
      allowNull: false,
    }
  },{
    timestamps: false,
    tableName: table_name, 
  });

  const Status = {
    Uploaded: "Uploaded",
    Unclenched: "Unclenched",
    ReadyToSend: "ReadyToSend",
    Delete: "Delete",
    Saved: "Saved",
  }

  return {File, Status};
};

