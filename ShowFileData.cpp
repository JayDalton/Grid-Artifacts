#include "pch.h"
#include "ShowFileData.h"
#if __has_include("ShowFileData.g.cpp")
#include "ShowFileData.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::GridArtifacts::implementation
{
    ShowFileData::ShowFileData()
    {
        InitializeComponent();
    }

    int32_t ShowFileData::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void ShowFileData::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

	Windows::Foundation::IAsyncAction ShowFileData::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs e)
	{
		File(e.Parameter().as<StorageFile>());

		if (auto file = File())
		{
			FileName().Text(file.Path());

			co_await file.GetBasicPropertiesAsync();
		}

		//BackButton().IsEnabled(Frame().CanGoBack());
		//return Windows::Foundation::IAsyncAction();
	}

    //void ShowFileData::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    //{
    //    Button().Content(box_value(L"Clicked"));
    //}
}
