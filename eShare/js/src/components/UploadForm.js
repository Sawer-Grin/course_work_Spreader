import { React } from "react";
import "../css/UploadForm.css";
import file from "../assets/file.svg";
import copy_icon from "../assets/copy-icon.svg";

const UploadForm = (props) => {
  const host = "http://127.0.0.1:8080/";
  const uploadURL = `${host}api/files`;
  const emailURL = `${host}api/files/send`;

  const dropZone = document.getElementsByClassName("drop-zone");
  const fileInput = document.getElementsByClassName("file-input");
  const bgProgress = document.getElementsByClassName("bg-progress");
  const percentDiv = document.getElementsByClassName("percent");
  const progressBar = document.getElementsByClassName("progress-bar");
  const progressContainer =
    document.getElementsByClassName("progress-container");
  const fileURL = document.getElementsByClassName("fileURL");
  const sharingContainer = document.getElementsByClassName("sharing-container");
  const emailForm = document.getElementsByClassName("email-form");
  const toast = document.getElementsByClassName("toast");
  const maxAllowedSize = 100 * 1024 * 1024;

  const handleDragOver = (e) => {
    e.preventDefault();
    if (!dropZone[0].classList.contains("dragged")) {
      dropZone[0].classList.add("dragged");
    }
  };

  const handleDragLeave = (e) => {
    dropZone[0].classList.remove("dragged");
  };

  const handleDrop = (e) => {
    e.preventDefault();

    dropZone[0].classList.remove("dragged");
    const files = e.dataTransfer.files;
    if (files.length) {
      fileInput[0].files = files;
      uploadFile();
    }
  };

  const handleChange = (e) => {
    uploadFile();
  };

  const handleClick = (e) => {
    fileInput[0].click();
  };

  const uploadFile = () => {
    if (fileInput[0].files.length > 1) {
      fileInput[0].value = "";
      showToast("Upload 1 file only!");
      return;
    }

    if (fileInput[0].files[0].size > maxAllowedSize) {
      fileInput[0].value = "";
      showToast("Can't upload more than 100MB");
      return;
    }

    progressContainer[0].style.display = "block";
    const file = fileInput[0].files[0];
    console.log(file);
    const formData = new FormData();
    formData.append("myfile", file);

    const xhr = new XMLHttpRequest();
    xhr.open("POST", "http://localhost:8080/api/files", true) ;
    xhr.onreadystatechange = () => {
      if (xhr.readyState === XMLHttpRequest.DONE) {
        showToast("File uploaded successfully");
        // console.log(xhr.response);
        showLink(JSON.parse(xhr.response));
      }
    };

    xhr.upload.onprogress = updateProgress;

    xhr.upload.onerror = () => {
      fileInput[0].value = "";
      showToast(`Error in upload: ${xhr.statusText}`);
    };

    xhr.open("POST", uploadURL);
    xhr.send(formData);
  };

  const updateProgress = (e) => {
    const percent = Math.round((e.loaded / e.total) * 100);
    bgProgress[0].style.width = `${percent}%`;
    progressBar[0].style.width = `${percent}%`;
    percentDiv[0].innerText = percent;
  };

  const showLink = ({ file: url }) => {
    progressContainer[0].style.display = "none";
    sharingContainer[0].style.display = "block";
    fileInput[0].value = "";
    fileURL[0].value = url;
  };

  const handleCopyClick = (e) => {
    fileURL[0].select();
    document.execCommand("copy");
    showToast("Link copied");
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    const url = fileURL[0].value;
    const formData = {
      uuid: url.split("/").splice(-1, 1)[0],
      emailTo: emailForm[0].elements["to-email"].value,
      emailFrom: emailForm[0].elements["from-email"].value,
    };
    console.log(formData);

    fetch(emailURL, {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(formData),
    })
      .then((res) => res.json())
      .then(({ success }) => {
        if (success) {
          sharingContainer[0].style.display = "none";
          showToast("Email sent successfully");
        }
      });
  };

  let toastTimer;
  const showToast = (msg) => {
    toast[0].innerText = msg;
    toast[0].style.transform = "translate(-50%, 0)";
    clearTimeout(toastTimer);
    toastTimer = setTimeout(() => {
      toast[0].style.transform = "translate(-50%, 60px)";
    }, 2500);
  };

  return (
    <>
      <section className="upload-container">
        <div
          className="drop-zone"
          onDragOver={handleDragOver}
          onDragLeave={handleDragLeave}
          onDrop={handleDrop}
        >
          <div className="icon-container">
            <img
              src={file}
              alt="file-icon"
              className="left"
              draggable="false"
            />
            <img
              src={file}
              alt="file-icon"
              className="center"
              draggable="false"
            />
            <img
              src={file}
              alt="file-icon"
              className="right"
              draggable="false"
            />
          </div>
          <input type="file" className="file-input" onChange={handleChange} />
          <div className="title">
            Drop your files here or,{" "}
            <span className="browseBtn" onClick={handleClick}>
              browse
            </span>
          </div>
        </div>
        <div className="progress-container">
          <div className="bg-progress"></div>
          <div className="inner-container">
            <div className="title">Uploading...</div>
            <div className="percent-container">
              <span className="percent">0</span>%
            </div>
            <div className="progress-bar"></div>
          </div>
        </div>
        <div className="sharing-container">
          <p class="expire">Link expires in 24 hours</p>
          <div className="input-container">
            <input type="text" className="fileURL" readOnly />
            <img
              src={copy_icon}
              alt="copy-icon"
              draggable="false"
              onClick={handleCopyClick}
            />
          </div>
          <p class="expire">Or send via email</p>
          <div className="email-container">
            <form className="email-form" onSubmit={handleSubmit}>
              <div className="field">
                <label for="sender">Your email</label>
                <input
                  type="email"
                  name="from-email"
                  className="sender"
                  required
                />
              </div>
              <div className="field">
                <label for="receiver">Receiver's email</label>
                <input
                  type="email"
                  name="to-email"
                  className="receiver"
                  required
                />
              </div>
              <button type="submit">Send</button>
            </form>
          </div>
        </div>
      </section>
      <div className="upload-vector"></div>
      <div className="toast"></div>
    </>
  );
};

export default UploadForm;
