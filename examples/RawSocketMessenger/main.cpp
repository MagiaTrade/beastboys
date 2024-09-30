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
      logI << "Stream1 closed with msg: " << data;
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
    logI << "Stream CLOSE CB!!!";
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
  std::shared_ptr<bb::RawStreamer> streamer(new bb::RawStreamer());

//  auto stream = streamer->openStream("stream.binance.com","9443","/ws/btcusdt@kline_1s",
  auto stream = streamer->openStream("localhost","12345","",
  [](bool success, const std::string& data, auto stream)
  {
    if(!success) {
      logI << "Stream1 closed with msg: " << data;
      return;
    }

    //Work with your streamed data here
    logI << data;
  });


  bool sent = false;
  auto messenger  = std::make_unique<bb::RawMessenger>();

  while(stream.lock()){
    // Do other stuff while the data is coming in callback
    std::this_thread::sleep_for(std::chrono::seconds(1));
//        logI << "\nWorking.. \n";

//    if(!sent)
//    {
//      messenger->sendMessage(stream.lock(),
//     "{\n\"method\": \"SUBSCRIBE\",\n\"params\":\n[\n\"btcusdt@trade\"\n],\n\"id\": 1\n}",
//     [](bool success) {
//       if (success)
//         logI << "Msg enviada com sucesso!\n";
//       else
//         logE << "Msg nao enviada!\n";
//     });
//
//      sent = true;
//    }

    if(!sent)
    {
      messenger->sendMessage(stream.lock(),
     "Oi amigao!",
     [](bool success) {
       if (success)
         logI << "Msg enviada com sucesso!";
       else
         logI << "Msg nao enviada!";
     });

      sent = true;
    }



  }

  return EXIT_SUCCESS;
}