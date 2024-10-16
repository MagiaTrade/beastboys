//
// Created by Arthur Motelevicz on 05/03/23.
//

#include <iostream>
#include <beastboys>

int main()
{
    std::shared_ptr<bb::Streamer> streamer(new bb::Streamer());

    std::weak_ptr<bb::network::ws::Stream> stream = streamer->openStream("stream.binance.com","9443","/ws/btcusdt@kline_1s", true,
    [](bool success, const std::string& data, auto stream){
        if(!success)
        {
          logI << "Stream1 closed with msg: " << data;
            return;
        }
      logW << "Stream active: " << stream->getId() << " Use count: " << stream.use_count();
      //Work with your streamed data here
      logI << data;
    });

    if(auto sharedStream = stream.lock())
      logW << "Stream requested: " << sharedStream->getId() << " Use count: " << sharedStream.use_count();


    bool sent = false;
    auto messenger  = std::make_unique<bb::Messenger>();
  std::string input;

    while(input != "q")
    {
      std::getline(std::cin,input);

      if(input == "subs" && !sent)
      {
          messenger->sendMessage(stream.lock(),
           "{\n\"method\": \"SUBSCRIBE\",\n\"params\":\n[\n\"btcusdt@trade\"\n],\n\"id\": 1\n}",
           [](bool success)
           {
             if (success)
               logI << "Msg enviada com sucesso!";
               else
               logE << "Msg nao enviada!";
           });

          sent = true;
      }
      //close stream
      else if(input == "k")
      {
        stream.lock()->stop();
      }

    }

    return 0;
}



