/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oalplus_source_common_1
namespace oalplus {

template <>
class __ObjectOps<__tag_DirectState, __tag_Source>
 : public __SourceName
{
public:
	void Play(void); /*<
	Starts the audio playback.
	See [alfunc SourcePlay].
	>*/
	void Pause(void); /*<
	Pauses the audio playback.
	See [alfunc SourcePause].
	>*/
	void Stop(void); /*<
	Stops the audio playback.
	See [alfunc SourceStop].
	>*/
	void Rewind(void); /*<
	Rewinds the audio track.
	See [alfunc SourceRewind].
	>*/


// TODO
};
//]
//[oalplus_source_def

typedef ObjectOps<__tag_DirectState, __tag_Source>
	SourceOps;

typedef __Object<SourceOps> Source;

} // namespace oalplus
//]

