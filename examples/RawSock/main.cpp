//
// Created by Arthur Motelevicz on 24/07/24.
//
#include <iostream>
#include <beastboys>

void localHostStream();

std::shared_ptr< bb::network::rs::Stream> createRawStream(const std::shared_ptr<bb::RawStreamer> & streamer){

//  auto stream = streamer->openStream("localhost","12345","",
  auto stream = streamer->openStream("datafeed1.cedrotech.com","81","",
  [](bool success, const std::string& data, auto stream){
    if(!success) {
      logI << "Stream1 closed with msg: " << data << "\n\n";
      //here in the client you can reschedule a reconnection routine
      return;
    }

    //Work with your streamed data here
    logI << data;
  });

  return std::move(stream.lock());

}
void rawStream(){
  std::shared_ptr<bb::RawStreamer> streamer(new bb::RawStreamer());

  auto stream = createRawStream(streamer);
  std::function<void(RawSharedStream)> closeCB = [&](RawSharedStream closedStream){
    logI << "Stream CLOSE CB!!! \n";
    stream = createRawStream(streamer);
    stream->setCloseStreamCallback(closeCB);
  };

  stream->setCloseStreamCallback(closeCB);

  stream->setCloseStreamCallback([&](RawSharedStream closedStream){
    closeCB(closedStream);
  });

  while(stream.use_count() > 1){
    // Do other stuff while the data is coming in callback
//        std::this_thread::sleep_for(std::chrono::seconds(3));
  }

}

int main()
{
  rawStream();
  return EXIT_SUCCESS;
}