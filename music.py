import youtube_dl
import discord
from discord.ext import commands



class music(commands.Cog):
    def __init__(self, client):
        self.client = client


    @commands.command()
    async def join(self,contexto):
        if contexto.author.voice is None:
            await contexto.send("No estas en un canal de voz")
        voice_channel = contexto.author.voice.channel
        if contexto.voice_client is None:
            await voice_channel.connect()
        else:
            await contexto.voice_client.move_to(voice_channel)


    @commands.command()
    async def disconnect(self,contexto):
        await contexto.voice_client.disconnect()

    @commands.command()
    async def play(self, contexto, url):
        contexto.voice_client.stop()
        FFMPEG_OPTIONS = {"before_options": "-reconnect 1 -reconnect_streamed 1 -reconnect_delay_max 5",
                              "options": "-vn"}
        YDL_OPTIONS = {"format": "bestaudio"}
        vc = contexto.voice_client
        url = url[1:-1]
        with youtube_dl.YoutubeDL(YDL_OPTIONS) as ydl:
            info = ydl.extract_info(url, download=False)
            url2 = info["formats"][0]["url"]
            vc.play(discord.FFmpegPCMAudio(executable="C:/webm/bin/ffmpeg.exe", source=url2, **FFMPEG_OPTIONS))

    @commands.command()
    async def pause(self,contexto):
        await contexto.voice_client.pause()


    @commands.command()
    async def resume(self, contexto):
        await contexto.voice_client.resume()

def setup(client):
    client.add_cog(music(client))
