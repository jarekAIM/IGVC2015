////////////////////////////////////////////////////////////////////////////////////
///
///  \file ReportImage.h
///  \brief This file contains the implementation of a JAUS message.
///
///  <br>Author(s): Daniel Barber
///  Created: 15 January 2010
///  Copyright (c) 2010
///  <br>Applied Cognition and Training in Immersive Virtual Environments
///  <br>(ACTIVE) Laboratory
///  <br>Institute for Simulation and Training (IST)
///  <br>University of Central Florida (UCF)
///  <br>All rights reserved.
///  <br>Email: dbarber@ist.ucf.edu
///  <br>Web:  http://active.ist.ucf.edu
///
///  Redistribution and use in source and binary forms, with or without
///  modification, are permitted provided that the following conditions are met:
///      * Redistributions of source code must retain the above copyright
///        notice, this list of conditions and the following disclaimer.
///      * Redistributions in binary form must reproduce the above copyright
///        notice, this list of conditions and the following disclaimer in the
///        documentation and/or other materials provided with the distribution.
///      * Neither the name of the ACTIVE LAB, IST, UCF, nor the
///        names of its contributors may be used to endorse or promote products
///        derived from this software without specific prior written permission.
/// 
///  THIS SOFTWARE IS PROVIDED BY THE ACTIVE LAB''AS IS'' AND ANY
///  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
///  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
///  DISCLAIMED. IN NO EVENT SHALL UCF BE LIABLE FOR ANY
///  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
///  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
///  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
///  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
///  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
///  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
////////////////////////////////////////////////////////////////////////////////////
#ifndef __JAUS_EXTRAS_VIDEO_REPORT_IMAGE__H
#define __JAUS_EXTRAS_VIDEO_REPORT_IMAGE__H

#include "jaus/extras/ExtrasCodes.h"
#include "jaus/core/Message.h"
#include <cxutils/images/Image.h>

namespace JAUS
{
    typedef CxUtils::Image Image;

    ////////////////////////////////////////////////////////////////////////////////////
    ///
    ///   \class ReportImage
    ///   \brief This message allows a component to publish an image or video
    ///          frame.
    ///
    ////////////////////////////////////////////////////////////////////////////////////
    class JAUS_EXTRAS_DLL ReportImage : public Message
    {
    public:
        ReportImage(const Address& dest = Address(), const Address& src = Address());
        ReportImage(const ReportImage& message);
        ~ReportImage();   
        void SetFrameNumber(const UInt fnumber) { mFrameNumber = fnumber; }
        void SetCameraID(const Byte id) { mCameraID = id; }
        void SetImageFormat(const Image::Format format) { mFormat = format; }
        void SetImage(const Image::Format format,
                      const Packet& imageData) { mFormat = format; mImage = imageData; }
        inline Byte GetCameraID() const { return mCameraID; }
        inline UInt GetFrameNumber() const { return mFrameNumber; }
        inline Image::Format GetFormat() const { return mFormat; }
        inline Packet* GetImage() { return &mImage; }
        inline const Packet* GetImage() const { return &mImage; }
        virtual bool IsCommand() const { return false; }
        virtual int WriteMessageBody(Packet& packet) const;
        virtual int ReadMessageBody(const Packet& packet);
        virtual Message* Clone() const { return new ReportImage(*this); }
        virtual UInt GetPresenceVector() const { return 0; }
        virtual UInt GetPresenceVectorSize() const { return 0; }
        virtual UInt GetPresenceVectorMask() const { return 0; }
        virtual UShort GetMessageCodeOfResponse() const { return 0; }
        virtual std::string GetMessageName() const { return "Report Image"; }
        virtual void ClearMessageBody();
        virtual bool IsLargeDataSet(const unsigned int maxPayloadSize) const;
        ReportImage& operator=(const ReportImage& message);
    protected:
        Image::Format mFormat;      ///<  Format of image data.
        Byte mCameraID;             ///<  Camera ID (number).
        UInt mFrameNumber;          ///<  Frame number.
        Packet mImage;              ///<  Image data.
    };
}

#endif
/*  End of File */
