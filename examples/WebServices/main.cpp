#include <Nazara/Core.hpp>
#include <Nazara/Network.hpp>
#include <iostream>

int main()
{
	Nz::Application<Nz::Network> app;

	std::unique_ptr<Nz::WebService> webService = Nz::Network::Instance()->InstantiateWebService();

	std::unique_ptr<Nz::WebRequest> webRequest = webService->CreateGetRequest("https://www.perdu.com", [&](const Nz::WebRequestResult& result)
	{
		if (result)
		{
			std::cout << "Got a " << result.GetReponseCode() << " response(" << result.GetDownloadedSize() << " bytes, " << result.GetDownloadSpeed() << " bytes / s" << ")" << std::endl;
			std::cout << result.GetBody() << std::endl;
		}
		else
			std::cout << "Web request failed (code " << result.GetReponseCode() << "): " << result.GetErrorMessage() << std::endl;

		Nz::ApplicationBase::Instance()->Quit();
	});

	webService->QueueRequest(std::move(webRequest));

	app.AddUpdaterFunc([&] { webService->Poll(); });

	return app.Run();
}
